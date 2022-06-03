#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// TODO: how are syscalls included?

#include "measurement_scenarios.h"
#include "helper_functions.h"
#include "scenario_runners.h"


int main(int argc, char *argv[])
{
	write_seq_n_times(MB(50), 10);

	// create_file_of_size("data_100M", 100);

	// printf("#############################\n");
	// printf("Writing a file randomly...\n");
	// srand(time(NULL));
	// write_randomly("data_100M", MB(30), MB(0.1), MB(1));

	// printf("#############################\n");
	// printf("Testing sequential write...\n");
	// write_seq(MB(30));

	// printf("#############################\n");
	// printf("Testing sequential read...\n");
	// read_seq(1026);

	// printf("#############################\n");
	// printf("Reading a file randomly...\n");
	// srand(time(NULL));
	// read_randomly("data_100M", MB(100), MB(0.1), MB(2));


	// printf("#############################\n");
	// printf("Testing sequentual reading...\n");
	// read_seq_existing("data_100M");

	// FILE *file = create_file_of_size("new_file_10M", 10);
	// file = fopen("new_file_10M", "r");
	// read_bytes(file, 1026);
	// fclose(file);
	// remove("new_file_10M");

	// printf("#############################\n");
	// printf("Creating a file...\n");
	// create_file(1000, "write_data");

	// printf("#############################\n");
	// printf("Testing directory listing...\n");
	// list_dir(5000);

	// printf("#############################\n");
	// printf("Testing sequential write with malloc...\n");
	// write_seq_malloc(MB(30));


	// printf("#############################\n");
	// printf("Testing creating & removing of files...\n");
	// create_remove_files(500);


	return 0;
}