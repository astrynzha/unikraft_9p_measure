#ifndef SCENARIO_RUNNERS_H
#define SCENARIO_RUNNERS_H

#include "helper_functions.h"

#include <stdio.h>

BYTES get_file_size(FILE *file);
void write_seq_runner(BYTES bytes, int measurements);
void write_seq_malloc_runner(BYTES bytes, int measurements);
void write_randomly_runner(const char *filename, BYTES bytes, BYTES lower_write_limit, BYTES upper_write_limit, int measurements);

void read_seq_runner(BYTES bytes, int measurements);
void read_seq_existing_runner(const char *filename, int measurements);
void read_randomly_runner(const char *filename, BYTES bytes, BYTES lower_read_limit, BYTES upper_read_limit, int measurements);

#endif