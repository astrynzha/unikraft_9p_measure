#ifndef SCENARIO_RUNNERS_H
#define SCENARIO_RUNNERS_H

#include "helper_functions.h"

#include <stdio.h>

FILE *create_file_of_size(const char *filename, BYTES bytes);

void create_files_runner(int file_amount, int measurements);
void remove_files_runner(int amount, int measurements);
void list_dir_runner(int file_amount, int measurements);

void write_seq_runner(BYTES bytes, int measurements);
void write_seq_malloc_runner(BYTES bytes, int measurements);
void write_randomly_runner(const char *filename, BYTES bytes, BYTES lower_write_limit, BYTES upper_write_limit, int measurements);

void read_seq_runner(BYTES bytes, int measurements);
void read_seq_existing_runner(const char *filename, int measurements);
void read_randomly_runner(const char *filename, BYTES bytes, BYTES lower_read_limit, BYTES upper_read_limit, int measurements);

#endif