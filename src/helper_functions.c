#include "helper_functions.h"

#ifdef __Unikraft__
#include "sys/random.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>




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
void read_bytes(int fd, BYTES bytes, BYTES buffer_size, char *buffer) {
	long long rc;

	BYTES iterations = bytes / buffer_size;
	BYTES rest = bytes % buffer_size;

	for (BYTES i = 0; i < iterations; i++) {
		rc = read(fd, buffer, buffer_size);
		if (rc == -1) {
			puts("Failed to read\n");
		}
	}
	if (rest > 0) {
		rc = read(fd, buffer, rest);
		if (rc == -1) {
			puts("Failed to read\n");
		}
	}
}

/*
    Writes `bytes` bytes with a 1KB buffer.
*/
void write_bytes(FILE *file, BYTES bytes, BYTES buffer_size)
{
	long long rc;
	int fd = fileno(file);

	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated. At %s, line %d. \n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	memset(buffer, '1', buffer_size);
	buffer[buffer_size - 1] = '\0';

	while (bytes >= buffer_size) {
		rc = write(fd, buffer, buffer_size);
		if (rc < 0) {
			puts("Failed to write\n");
		}
		// if (buffer_size != fwrite(buffer, 1, (size_t) buffer_size, file)) {
		// 	puts("Failed to write\n");
		// }

		bytes -= buffer_size;
	}

	BYTES rest = bytes % buffer_size;
	if (rest > 0) {
		rc = write(fd, buffer, rest);
		if (rc < 0) {
			puts("Failed to write\n");
		}
		// if (rest != fwrite(buffer, sizeof(char), rest, file)) {
		// 	puts("Failed to write");
		// }
	}

	free(buffer);
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


/**
 * @brief calculate the file intervals and the order, in which to read / write
 * them
 *
 * The caller is responsible for freeing the memory, allocated for the
 * output variables.
 *
 * @param file_size
 * @param[out] file_chunks
 * @param[out] interval_order
 * @param[out] num_intervals
 */
void slice_file(BYTES file_size, struct file_interval **intervals,
		BYTES **interval_order, BYTES *num_intervals)
{
	// BYTES interval_len = MB(1);
	BYTES interval_len = MB(1);
	BYTES full_intervals = file_size / interval_len;
	BYTES total_intervals;

	if (file_size % interval_len) {
		total_intervals = full_intervals + 1;
	} else {
		total_intervals = full_intervals;
	}

	*intervals = malloc(sizeof(struct file_interval)
		* total_intervals);
	*interval_order = malloc(sizeof(BYTES)
		* total_intervals);
	if (total_intervals > full_intervals) {
		((*intervals)[full_intervals]).off = interval_len * full_intervals;
		((*intervals)[full_intervals]).len = file_size % interval_len;
	}

	for (BYTES i = 0; i < full_intervals; i++) {
		((*intervals)[i]).off = interval_len * i;
		((*intervals)[i]).len = interval_len;
	}

	char *bitmap = calloc(total_intervals, 1);

	for (BYTES i = 0; i < total_intervals; i++) {
		BYTES r_number;

		do {
			#ifdef __linux__
			r_number = rand();
			#elif __Unikraft__
			getrandom(&r_number,sizeof(BYTES), 0);
			#endif

			r_number = r_number % total_intervals;
		} while (bitmap[r_number]);

		(*interval_order)[i] = r_number;
		bitmap[r_number] = 1;
	}

	*num_intervals = total_intervals;

	free(bitmap);
}