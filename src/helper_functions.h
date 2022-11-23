#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <stdio.h>
#include <math.h>

// #define NDEBUG
#include <assert.h>

#define DEBUGMODE 1
#ifdef DEBUGMODE
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
// how many digits a number has. Cannot be less than 1.
#define DIGITS(num) ((int)((ceil(log10(MAX(num, 1))+1)*sizeof(char))))

typedef unsigned long long BYTES;
typedef unsigned long FILES;

#define KB(n) ((BYTES) (n)*1024)
#define MB(n) ((BYTES) ((n) * KB(1024)))
#define GB(n) ((BYTES) ((n) * MB(1024)))
#define B_TO_KB(n) ((BYTES) ((n) / 1024))
#define B_TO_MB(n) ((BYTES) ((n) / 1024 / 1024))
#define B_TO_GB(n) ((BYTES) ((n) / 1024 / 1024 / 1024))

struct file_interval {
	BYTES off;
	BYTES len;
};


BYTES get_file_size(FILE *file);
BYTES sample_in_range(BYTES lower, BYTES upper);
void read_bytes(int fd, BYTES bytes, BYTES buffer_size, char *buffer);
void write_bytes(FILE *file, BYTES bytes, BYTES buffer_size);
void init_filenames(FILES file_amount, int max_filename_length, char *file_names);
void slice_file(BYTES file_size, struct file_interval **intervals,
		BYTES **interval_order, BYTES *num_intervals,
		BYTES interval_len);

#endif