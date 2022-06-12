#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// TODO: how are syscalls included?

#include "measurement_scenarios.h"
#include "helper_functions.h"
#include "scenario_runners.h"


int main(int argc, char *argv[])
{
	// create_file_of_size("data_100M", MB(100));

	// list_dir_runner(15000, 5);
	// create_files_runner(5000, 4);
	// remove_files_runner(5000, 4);

	// read_randomly_runner("data_100M", MB(100), MB(0.1), MB(1), 4);
	// read_seq_existing_runner("data_100M", 4);
	read_seq_runner("data_100M", MB(50), MB(5), 4);	

	// write_randomly_runner("data_100M", MB(50), MB(5), MB(0.1), MB(1), 4);
	// write_seq_runner(MB(50), MB(5), 4);

	return 0;
}