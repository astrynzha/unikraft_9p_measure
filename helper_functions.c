#include "helper_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // TODO: where is it included from?

BYTES get_file_size(FILE *file) {
	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	rewind(file);
	return size;
}

/*
    Creates a file, filled with 'Z' charachters, of size `bytes`, with a given filename
*/
FILE *create_file_of_size(const char *filename, BYTES bytes) {
	FILE *file;
	BYTES buffer_size = KB(1); // TODO: warum kann buffer nicht beliebig gross werden?
	char buffer[buffer_size];

	for (BYTES i = 0; i < buffer_size; i++) {
		buffer[i] = 'X';
	}

	file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

	for (BYTES i = 0; i < B_TO_KB(bytes); i++) {
		fwrite(buffer, sizeof(char), buffer_size, file);
	}
    BYTES rest = bytes % buffer_size;
    if (rest > 0) {
		if (rest != fwrite(buffer, sizeof(char), rest, file)) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
    }
	
	fclose(file);

	printf("File %s of size %lluB created\n", filename, bytes);

	return file;
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
void init_filenames(int file_amount, int file_name_reserved_length, char file_names[][file_name_reserved_length]) {
	for (int i = 0; i < file_amount; i++) {
		char suffix[7 + DIGITS(i)];
		sprintf(suffix, "file_%d", i);
		strcpy(file_names[i], suffix);
	}
}
