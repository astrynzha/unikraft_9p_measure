#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "measurement_scenarios.h"
#include "helper_functions.h"
#include "scenario_runners.h"

/* returns base to the power of exp */
BYTES bpow(BYTES base, BYTES exp)
{
    BYTES result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int main(int argc, char *argv[])
{
	#ifdef __linux__
	char platform[6] = "Linux";
    chdir("guest_fs");
	#elif __Unikraft__
	char platform[9] = "Unikraft";
	#endif
	DEBUG_PRINT("__________________________\n");
	DEBUG_PRINT("Running in DEBUGMODE\n");
	DEBUG_PRINT("Running on %s\n", platform);
	DEBUG_PRINT("__________________________\n");

	// create_file_of_size("data_100M", MB(100));

	int max_pow = 17;
	FILES amount[max_pow];
	puts("amount");
	for (int i = 0; i < max_pow; i++) { // buffer_sizes = {16, 32, 64, ..., 2^max_pow}
		amount[i] = bpow(2, i + 1);
		printf("%lu\n", amount[i]);
	}

	// create_files_runner(amount, 17, 10);
	// remove_files_runner(amount, 17, 10);
	// list_dir_runner(amount, 17, 10);

	int max_pow2 = 20;
	int min_pow2 = 4;
	int arr_size = max_pow2 - min_pow2 + 1;

	BYTES bytes_arr_FUSE[arr_size];
	BYTES buffer_size_arr[arr_size];
	BYTES interval_len_arr[arr_size];

	BYTES bytes_arr_DAX[arr_size];

	printf("buffer sizes\n");
	for (int i = min_pow2; i < max_pow2 + 1; i++) { // buffer_sizes = {16, 32, 64, ..., 2^max_pow}
		buffer_size_arr[i-min_pow2] = bpow(2, i);
		bytes_arr_FUSE[i-min_pow2] = buffer_size_arr[i-min_pow2] * bpow(2, 13);
		bytes_arr_DAX[i-min_pow2] = bpow(2, 20 + 13);
		// bytes_arr_DAX[i-min_pow2] = 100 * bpow(2, 20);
		interval_len_arr[i-min_pow2] = buffer_size_arr[i-min_pow2];
		printf("buffer_size: %llu\n\
			bytes: %llu\n\
			interval_len: %llu\n\
			---------------------\n",
			buffer_size_arr[i - min_pow2],
			bytes_arr_FUSE[i-min_pow2],
			interval_len_arr[i-min_pow2]);
	}
	int measurements = 3;

	#ifdef __linux__

	// write_seq_runner("1G_file", bytes_arr_DAX,
	// 		buffer_size_arr, arr_size, measurements);
	// write_randomly_runner("1G_file", bytes_arr_DAX,
	// 		buffer_size_arr, interval_len_arr, arr_size,
	// 		measurements);

	// read_seq_runner("1G_file", bytes_arr_DAX,
	// 		buffer_size_arr, arr_size, measurements);
	read_randomly_runner("1G_file", bytes_arr_DAX,
			buffer_size_arr, interval_len_arr, arr_size,
			measurements);

	#elif __Unikraft__

	write_seq_runner("1G_file", bytes_arr_FUSE,
			buffer_size_arr, arr_size, measurements);
	write_randomly_runner("1G_file", bytes_arr_FUSE,
			buffer_size_arr, interval_len_arr, arr_size,
			measurements);

	read_seq_runner("1G_file", bytes_arr_FUSE,
			buffer_size_arr, arr_size, measurements);
	read_randomly_runner("1G_file", bytes_arr_FUSE,
			buffer_size_arr, interval_len_arr, arr_size,
			measurements);

	#endif

	return 0;
}
