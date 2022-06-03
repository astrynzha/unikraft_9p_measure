#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// TODO: how are syscalls included?

#include "measurement_scenarios.h"
#include "helper_functions.h"
#include "scenario_runners.h"


int main(int argc, char *argv[])
{
	create_file_of_size("data_100M", MB(100));

	read_randomly_runner("data_100M", MB(50), MB(0.1), MB(1), 4);
	read_seq_existing_runner("data_100M", 4);
	read_seq_runner(MB(50), 4);	

	write_randomly_runner("data_100M", MB(50), MB(0.1), MB(1), 4);
	write_seq_malloc_runner(MB(50), 4);
	write_seq_runner(MB(50), 4);

	return 0;
}