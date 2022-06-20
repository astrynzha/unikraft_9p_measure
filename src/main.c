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

	// FILES amount[] = {10, 100, 500, 1000, 2500, 5000, 10000, 20000, 50000, 100000};
	// create_files_runner(amount, 10, 10);
	// remove_files_runner(amount, 10, 4);
	// list_dir_runner(amount, 10, 5);

	int max_pow = 28;
	BYTES buffer_sizes[max_pow-3];
	for (int i = 0; i < max_pow-3; i++) { // buffer_sizes = {16, 32, 64, ..., 2^max_pow}
		buffer_sizes[i] = bpow(2, i+4);
	} 

	// write_seq_runner(MB(50), buffer_sizes, max_pow-3, 4);
	// write_randomly_runner("data_100M", MB(50), buffer_sizes, max_pow-3, MB(0.01), MB(1), 4);

	read_seq_runner("data_100M", MB(100), buffer_sizes, max_pow-3, 4);	
	// read_randomly_runner("data_100M", MB(100), buffer_sizes, max_pow-3, MB(0.01), MB(1), 4);

	return 0;
}
