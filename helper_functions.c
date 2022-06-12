#include "helper_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BYTES get_file_size(FILE *file) {
	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	rewind(file);
	return size;
}


/*
   Samples natrual numbers in range [lower; upper)
*/
BYTES sample_in_range(BYTES lower, BYTES upper) {
	return (rand() % (upper - lower)) + lower;
}

/*
    Reads `bytes` bytes with a 1KB buffer.
*/
void read_bytes(FILE *file, BYTES bytes) {
	BYTES buffer_size = KB(1);
	char *buffer[buffer_size];
	while (bytes > buffer_size) {
		if (buffer_size != fread(buffer, 1, (size_t) buffer_size, file)) {
			puts("Failed to read\n");
		}
		bytes -= buffer_size;
	}

    BYTES rest = bytes % buffer_size;
    if (rest > 0) {
        if (rest != fread(buffer, sizeof(char), (size_t) rest, file)) {
            puts("Failed to read");
        }
    }
}

/*
    Writes `bytes` bytes with a 1KB buffer.
*/
void write_bytes(FILE *file, BYTES bytes) {
	BYTES buffer_size = 1024;
	char buffer[buffer_size];
	for (BYTES i = 0; i < buffer_size; i++) {
		buffer[i] = 'X';
	}

	while (bytes > buffer_size) {
		if (buffer_size != fwrite(buffer, 1, (size_t) buffer_size, file)) {
			puts("Failed to write\n");
		}
		bytes -= buffer_size;
	}

    BYTES rest = bytes % buffer_size;
    if (rest > 0) {
        if (rest != fwrite(buffer, sizeof(char), rest, file)) {
            puts("Failed to write");
        }
    }
}

/* 
    Initializing file names of kind: "file_0", "file_1", "file_2" and so on

*/
void init_filenames(FILES file_amount, int max_filename_length, char *file_names) {
	for (FILES i = 0; i < file_amount; i++) {
		char suffix[7 + DIGITS(i)];
		sprintf(suffix, "file_%lu", i);
		strcpy(file_names + i*max_filename_length, suffix);
	}
}