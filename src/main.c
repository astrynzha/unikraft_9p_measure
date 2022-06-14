#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "measurement_scenarios.h"
#include "helper_functions.h"
#include "scenario_runners.h"


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

	create_file_of_size("data_100M", MB(100));

	// list_dir_runner(150000, 5);
	// create_files_runner(5000, 4);
	// remove_files_runner(5000, 4);

	// read_randomly_runner("data_100M", MB(100), 64, MB(0.1), MB(1), 4);
	// read_seq_runner("data_100M", MB(100), 64, 4);	

	// write_randomly_runner("data_100M", MB(50), MB(5), MB(0.1), MB(1), 4);
	// write_seq_runner(MB(50), MB(5), 4);

	return 0;
}