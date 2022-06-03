#include "measurement_scenarios.h"
#include "helper_functions.h"

#include <uk/plat/time.h> // TODO: how does the build system find this path?
#include <dirent.h>
#include <stdlib.h>

/*
    Measure creating and removing `file_amount` files.

    Necessary files are created and deleted by the function.
*/
void create_remove_files(int file_amount) {
	__nsec create_start, creat_end, delete_start, delete_end, time_ms;

    int max_file_name_length = 7 + DIGITS(file_amount - 1);
	char file_names[file_amount][max_file_name_length]; 
    init_filenames(file_amount, max_file_name_length, file_names);

    // measuring the creation of file_amount files

	create_start = ukplat_monotonic_clock();
	for (int i = 0; i < file_amount; i++) {
		FILE *file = fopen(file_names[i], "w");
	    if (file == NULL) {
            fprintf(stderr, "Error creating file number %d.\n", i);
            exit(EXIT_FAILURE);
        }
		fclose(file);
	}
	creat_end = ukplat_monotonic_clock();

    // measuring the delition of file_amount files

	delete_start = ukplat_monotonic_clock();
	for (int i = 0; i < file_amount; i++) {
		if (remove(file_names[i]) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_names[i]);
		}
	}
	delete_end = ukplat_monotonic_clock();

	time_ms = ukarch_time_nsec_to_msec(creat_end - create_start);
	printf("Creating %d files took: %ldms %.3fs \n", file_amount, time_ms, (double) time_ms / 1000);

	time_ms = ukarch_time_nsec_to_msec(delete_end - delete_start);
	printf("Deleting %d files took: %ldms %.3fs \n", file_amount, time_ms, (double) time_ms / 1000);
}

/*
    Measure listing (e.g. ls command) of `file_amount` files.

    Necessary files are created and deleted by the function.
*/
void list_dir(int file_amount) {
	__nsec start, end, time_ms;

    int max_file_name_length = 7 + DIGITS(file_amount - 1);
	char file_names[file_amount][max_file_name_length]; 
    init_filenames(file_amount, max_file_name_length, file_names);

    // creating files
	for (int i = 0; i < file_amount; i++) {
		FILE *file = fopen(file_names[i], "w");
	    if (file == NULL) {
            fprintf(stderr, "Error creating file number %d.\n", i);
            exit(EXIT_FAILURE);
        }
		fclose(file);
	}

	start = ukplat_monotonic_clock();

	DIR *dp;
	struct dirent *ep;     
	dp = opendir ("./");
    if (dp == NULL) {
		fprintf(stderr, "Couldn't open the directory\n");
    }

    while (ep = readdir (dp)) {
        puts(ep->d_name);
    }

    (void) closedir (dp);

	end = ukplat_monotonic_clock();
	time_ms = ukarch_time_nsec_to_msec(end - start);
	printf("Listing %d files took: %ldms %.3fs \n", file_amount, time_ms, (double) time_ms / 1000);

    // deleting all created files

	for (int i = 0; i < file_amount; i++) {
		if (remove(file_names[i]) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_names[i]);
		}
	}
}

/*
    Measuring sequential write of `megabytes` megabytes.

    File is created and deleted by the function.
*/
__nsec write_seq(BYTES bytes) {
	FILE *file;
	file = fopen("write_data", "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file 'write_data'.\n");
		exit(EXIT_FAILURE);
	}

	BYTES buffer_size = KB(1); // TODO: warum kann buffer nicht beliebig gross werden?
	char buffer[buffer_size];

	for (BYTES i = 0; i < buffer_size; i++) {
		buffer[i] = 'X';
	}

	__nsec start, end, time_ms;

	start = ukplat_monotonic_clock();

	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
		if (buffer_size != fwrite(buffer, sizeof(char), buffer_size, file)) {
			fprintf(stderr, "Failed to write\n");
		}
	}
    BYTES rest = bytes % buffer_size;
	if (rest > 0) {
		if (rest != fwrite(buffer, sizeof(char), rest, file)) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
	}

	end = ukplat_monotonic_clock();

	fclose(file);

	printf("File \"write_data\" was written\n");

	time_ms = ukarch_time_nsec_to_msec(end - start);

	printf("Writing %llu megabytes took: %ldms %.3fs \n", B_TO_MB(bytes), time_ms, (double) time_ms / 1000);

	if (remove("write_data") == 0) {
		printf("Cleaned up data successfully\n");
	} else {
		fprintf(stderr, "Failed to remove \"write_data\" file\n");
	}

    return end - start;
}

/*
    Measuring sequential write with buffer on heap, allocated with malloc.
    
    File is created and deleted by the function
*/
void write_seq_malloc(BYTES bytes) {
	FILE *file;

	BYTES buffer_size = KB(1);
	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated.\n");
		exit(0);
	} 

	__nsec start, end, time_ms;
	start = ukplat_monotonic_clock();

	file = fopen("/write_data", "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '/write_data'.\n");
		exit(EXIT_FAILURE);
	}	

	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
		fwrite(buffer, buffer_size, 1, file);
	}

	end = ukplat_monotonic_clock();

	fclose(file);
	free(buffer);

	time_ms = ukarch_time_nsec_to_msec(end - start);

	printf("Writing %llu megabytes took: %ldms %.3fs \n", B_TO_MB(bytes),
	time_ms, (double) time_ms / 1000);

	if (remove("write_data") == 0) {
		printf("Cleaned up data successfully\n");
	} else {
		fprintf(stderr, "Failed to remove \"write_data\" file\n");
	}
}

/*
    Measuring random access write (non-sequential) of an existing file, passed to the function. 
    Seed has to be set by the caller.

    
    The function:
    1. Randomly determines a file position from range [0, EOF - upper_write_limit).
    2. Writes a random amount of bytes, sampled from range [lower_write_limit, upper_write_limit].
    3. Repeats steps 1-2 until the 'remeaining_bytes' amount of bytes is written.
*/
void write_randomly(const char *filename, BYTES remeaining_bytes, BYTES lower_write_limit, BYTES upper_write_limit) {
    BYTES megabytes_to_write = B_TO_MB(remeaining_bytes);
    // TODO: set seed = time
	FILE *file;
	file = fopen(filename, "r+");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}
	BYTES size = get_file_size(file);

	__nsec start, end, time_ms;

	start = ukplat_monotonic_clock();

	long int position;
	while (remeaining_bytes > upper_write_limit) {
		position = (long int) sample_in_range(0ULL, size - upper_write_limit);
		fseek(file, position, SEEK_SET);
		BYTES bytes_to_write = sample_in_range(lower_write_limit, upper_write_limit);
		write_bytes(file, bytes_to_write);
		remeaining_bytes -= bytes_to_write;
	}
	position = (long int) sample_in_range(0, size - upper_write_limit);
	fseek(file, position, SEEK_SET);
	write_bytes(file, remeaining_bytes);

	end = ukplat_monotonic_clock();

	fclose(file);

	time_ms = ukarch_time_nsec_to_msec(end - start);

	printf("Random writing of %llu megabytes took: %ldms %.3fs \n", megabytes_to_write, time_ms, (double) time_ms / 1000);
}

/*
    Measure sequential read of `megabytes` megabytes.

    File is first created by the function, read and then deleted.
*/
void read_seq(BYTES bytes) {
	FILE *file;
	BYTES buffer_size = KB(1); // TODO: warum kann buffer nicht beliebig gross werden?
    BYTES rest = bytes % buffer_size;
	char buffer[buffer_size];

	for (BYTES i = 0; i < buffer_size; i++) {
		buffer[i] = 'X';
	}

    // creating a file

    char *filename = "read_data";
	file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "On write: error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
		fwrite(buffer, sizeof(char), buffer_size, file);
	}
	if (rest > 0) {
		if (rest != fwrite(buffer, sizeof(char), rest, file)) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
	}
	
	fclose(file);

    // measuring sequential read

	__nsec start, end, time_ms;

	start = ukplat_monotonic_clock();
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "On read: error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}
	
	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
		if (buffer_size != fread(buffer, sizeof(char), buffer_size, file)) { //TODO: always false?
			fprintf(stderr, "Failed to read on iteration #%llu\n", i);
		}
	}
	if (rest > 0) {
		if (rest != fread(buffer, sizeof(char), rest, file)) {
			fprintf(stderr, "Failed to read the rest of the file\n");
		}
	}
    // TODO: read the rest (if bytes % 1024 != 0)

	end = ukplat_monotonic_clock();

	fclose(file);

	time_ms = ukarch_time_nsec_to_msec(end - start);

	printf("Reading %llu megabytes took: %ldms %.3fs \n", B_TO_MB(bytes), time_ms, (double) time_ms / 1000);

	if (remove(filename) == 0) {
		printf("Cleaned up data successfully\n");
	} else {
		fprintf(stderr, "Failed to remove \"%s\" file\n", filename);
	}

}


/*
    Measuring sequential read.

    The file is provided by the caller and not deleted in the end.
*/
void read_seq_existing(const char *filename) {
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

	BYTES buffer_size = 1024; // TODO: warum kann buffer nicht beliebig gross werden?
	char buffer[buffer_size];

	BYTES size = get_file_size(file);
	BYTES iterations = size / buffer_size;
	BYTES rest = size % buffer_size;

	__nsec start, end, time_ms;

	start = ukplat_monotonic_clock();
	
	for (BYTES i = 0; i < iterations; i++) {
		if (buffer_size != fread(buffer, sizeof(char), buffer_size, file)) {
			fprintf(stderr, "Failed to read on iteration #%llu\n", i);
		}
	}
	if (rest > 0) {
		if (rest != fread(buffer, sizeof(char), rest, file)) {
			fprintf(stderr, "Failed to read the rest of the file\n");
		}
	}

	end = ukplat_monotonic_clock();

	fclose(file);

	time_ms = ukarch_time_nsec_to_msec(end - start);

	printf("Reading %llu megabytes took: %ldms %.3fs \n", B_TO_MB(size), time_ms, (double) time_ms / 1000);
}

/*
    Measuring random access read (non-sequential). Seed has to be set by the caller.
    
    The function:
    1. Randomly determines a file position from range [0, EOF - upper_read_limit).
    2. Reads a random amount of bytes, sampled from range [lower_read_limit, upper_read_limit].
    3. Repeats steps 1-2 until the 'remeaning_bytes' amount of bytes is read.
    
    File is provided by the caller.
*/
void read_randomly(const char *filename, BYTES remaining_bytes, BYTES lower_read_limit, BYTES upper_read_limit) {
    BYTES megabytes_to_read = B_TO_MB(remaining_bytes); // TODO: make floaing point

	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}
	BYTES size = get_file_size(file);

	__nsec start, end, time_ms;

	start = ukplat_monotonic_clock();

	long int position;
	while (remaining_bytes > upper_read_limit) {
		position = (long int) sample_in_range(0, size - upper_read_limit);
		fseek(file, position, SEEK_SET);
		BYTES bytes_to_read = sample_in_range(lower_read_limit, upper_read_limit);
		read_bytes(file, bytes_to_read);
		remaining_bytes -= bytes_to_read;
	}
	position = sample_in_range(0, size - upper_read_limit);
	fseek(file, position, SEEK_SET);
	read_bytes(file, remaining_bytes);

	end = ukplat_monotonic_clock();

	fclose(file);

	time_ms = ukarch_time_nsec_to_msec(end - start);

	printf("Random reading of %llu megabytes took: %ldms %.3fs \n", megabytes_to_read, time_ms, (double) time_ms / 1000);
}