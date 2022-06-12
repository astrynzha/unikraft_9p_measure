#include "measurement_scenarios.h"
#include "helper_functions.h"

#include <uk/plat/time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


/*
    Measure removing `amount` files.

    Necessary files are created and deleted by the function.
*/
__nsec create_files(FILES amount) {
	__nsec start, end;

	// initializing file names 

    int max_file_name_length = 7 + DIGITS(amount - 1);
	char *file_names = (char*) malloc(amount*max_file_name_length); // 2D array
	init_filenames(amount, max_file_name_length, file_names);

    // measuring the creation of `amount` files

	start = ukplat_monotonic_clock();

	for (FILES i = 0; i < amount; i++) {
		FILE *file = fopen(file_names + i * max_file_name_length, "w");
	    if (file == NULL) {
            fprintf(stderr, "Error creating file number %lu.\n", i);
            exit(EXIT_FAILURE);
        }
		fclose(file);
	}

	end = ukplat_monotonic_clock();

    // cleaning up: deleting all files

	for (FILES i = 0; i < amount; i++) {
		char *file_name = file_names + i * max_file_name_length;
		if (remove(file_name) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_name);
		}
	}

    return end - start;
}

/*
    Measure creating `amount` files.

    Necessary files are created and deleted by the function.
*/
__nsec remove_files(FILES amount) {
    __nsec start, end;

	// initializing file names

    int max_file_name_length = 7 + DIGITS(amount - 1);
	char *file_names = (char*) malloc(amount*max_file_name_length); // 2D array
	init_filenames(amount, max_file_name_length, file_names);

    // creating `amount` empty files

	for (FILES i = 0; i < amount; i++) {
		FILE *file = fopen(file_names + i*max_file_name_length, "w");
	    if (file == NULL) {
            fprintf(stderr, "Error creating file number %lu.\n", i);
            exit(EXIT_FAILURE);
        }
		fclose(file);
	}

    // measuring the delition of `amount` files

	start = ukplat_monotonic_clock();
	for (FILES i = 0; i < amount; i++) {
		char *file_name = file_names + i * max_file_name_length;
		if (remove(file_name) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_name);
		}
	}
	end = ukplat_monotonic_clock();

    return end - start;
}

/*
    Measure listing (e.g. ls command) of files. 'file_amount'
	specifies how many files are in the directory.

    Necessary files are to be created and deleted by the caller
*/
__nsec list_dir(FILES file_amount) {
	__nsec start, end;

	start = ukplat_monotonic_clock();

	DIR *dp;
	struct dirent *ep;     
	dp = opendir ("./");
    if (dp == NULL) {
		fprintf(stderr, "Couldn't open the directory\n");
    }

	char str[256];
	// TODO: add to debug:
	// FILES file_count = 0;
    while ( (ep = readdir (dp)) ) {
		strcpy(str, ep->d_name); // using filenames somehow
		// TODO: add to debug;
		// file_count++; 
    }
    (void) closedir (dp);

	end = ukplat_monotonic_clock();

	// TODO: add to debug or as an assertion. Or maybe just delete
	/*
	file_amount += 2; // including "./" and "../" entries
	if (file_amount != file_count) {
		fprintf(stderr, "ERROR: Directory contains %lu files. %lu was expected.\n", file_count, file_amount);
	}
	*/

    return end - start;
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

	BYTES buffer_size = KB(1);
	char buffer[buffer_size];

	for (BYTES i = 0; i < buffer_size; i++) {
		buffer[i] = 'X';
	}

	__nsec start, end;

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

	if (!remove("write_data") == 0) {
		fprintf(stderr, "Failed to remove \"write_data\" file\n");
	}

    return end - start;
}

/*
    Measuring sequential write with buffer on heap, allocated with malloc.
    
    File is created and deleted by the function
*/
__nsec write_seq_malloc(BYTES bytes) {
	FILE *file;

	BYTES buffer_size = KB(1);
	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated.\n");
		exit(0);
	} 

	file = fopen("/write_data", "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '/write_data'.\n");
		exit(EXIT_FAILURE);
	}	

	__nsec start, end;
	start = ukplat_monotonic_clock();

	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
		fwrite(buffer, buffer_size, 1, file);
	}
    BYTES rest = bytes % buffer_size;
	if (rest > 0) {
		if (rest != fwrite(buffer, sizeof(char), rest, file)) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
	}

	end = ukplat_monotonic_clock();

	fclose(file);
	free(buffer);

	if (!remove("write_data") == 0) {
		fprintf(stderr, "Failed to remove \"write_data\" file\n");
	}

    return end - start;
}

/*
    Measuring random access write (non-sequential) of an existing file, passed to the function. 
    Seed has to be set by the caller.

    
    The function:
    1. Randomly determines a file position from range [0, EOF - upper_write_limit).
    2. Writes a random amount of bytes, sampled from range [lower_write_limit, upper_write_limit].
    3. Repeats steps 1-2 until the 'remeaining_bytes' amount of bytes is written.
*/
__nsec write_randomly(FILE *file, BYTES remeaining_bytes, BYTES lower_write_limit, BYTES upper_write_limit) {
	BYTES size = get_file_size(file);

	__nsec start, end;

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

    return end - start;
}

/*
    Measure sequential read of `megabytes` megabytes.

    File is first created by the function, read and then deleted.
*/
__nsec read_seq(FILE *file, BYTES bytes) {
	BYTES buffer_size = KB(1);
    BYTES rest = bytes % buffer_size;
	char buffer[buffer_size];

    // measuring sequential read

	__nsec start, end;

	start = ukplat_monotonic_clock();
	
	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
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


    return end - start;
}


/*
    Measuring sequential read.

    The file is provided by the caller and not deleted in the end.
*/
__nsec read_seq_existing(FILE *file) {
	BYTES buffer_size = KB(1);
	char buffer[buffer_size];

	BYTES size = get_file_size(file);
	BYTES iterations = size / buffer_size;
	BYTES rest = size % buffer_size;

	__nsec start, end;

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

    return end - start;
}

/*
    Measuring random access read (non-sequential). Seed has to be set by the caller.
    
    The function:
    1. Randomly determines a file position from range [0, EOF - upper_read_limit).
    2. Reads a random amount of bytes, sampled from range [lower_read_limit, upper_read_limit].
    3. Repeats steps 1-2 until the 'remeaning_bytes' amount of bytes is read.
    
    File is provided by the caller.
*/
__nsec read_randomly(FILE *file, BYTES remaining_bytes, BYTES lower_read_limit, BYTES upper_read_limit) {
	BYTES size = get_file_size(file);

	__nsec start, end;

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

    return end - start;
}