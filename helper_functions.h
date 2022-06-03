#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <stdio.h>
#include <math.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
// how many digits a number has. Cannot be less than 1.
#define DIGITS(num) ((int)((ceil(log10(MAX(num, 1))+1)*sizeof(char))))

#define KB(n) ((BYTES) (n)*1024)
#define MB(n) ((BYTES) ((n) * KB(1024)))
#define GB(n) ((BYTES) ((n) * MB(1024)))
#define B_TO_KB(n) ((BYTES) ((n) / 1024))
#define B_TO_MB(n) ((BYTES) ((n) / 1024 / 1024))
#define B_TO_GB(n) ((BYTES) ((n) / 1024 / 1024 / 1024))

typedef unsigned long long BYTES;

BYTES get_file_size(FILE *file);
FILE *create_file_of_size(const char *filename, BYTES megabytes);
BYTES sample_in_range(BYTES lower, BYTES upper);
void read_bytes(FILE *file, BYTES bytes);
void write_bytes(FILE *file, BYTES bytes);
void init_filenames(int file_amount, int file_name_reserved_length, char file_names[][file_name_reserved_length]);

#endif