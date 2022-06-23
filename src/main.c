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

	create_files_runner(amount, 17, 10);
	remove_files_runner(amount, 17, 10);
	list_dir_runner(amount, 17, 10);

	int max_pow2 = 27;
	BYTES buffer_sizes[max_pow2-3];
	puts("buffer sizes");
	for (int i = 0; i < max_pow2-3; i++) { // buffer_sizes = {16, 32, 64, ..., 2^max_pow}
		buffer_sizes[i] = bpow(2, i+4);
		printf("%llu\n", buffer_sizes[i]);
	} 


	write_seq_runner(MB(100), buffer_sizes, max_pow2-3, 10);
	write_randomly_runner("data_100M", MB(100), buffer_sizes, max_pow2-3, MB(0.01), MB(0.1), 10);

	read_seq_runner("data_100M", MB(100), buffer_sizes, max_pow2-3, 10);	
	read_randomly_runner("data_100M", MB(100), buffer_sizes, max_pow2-3, MB(0.01), MB(0.1), 10);

	return 0;
}
