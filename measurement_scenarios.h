#ifndef MEASUREMENT_SCENARIOS_H
#define MEASUREMENT_SCENARIOS_H

#include <stdio.h>
#include <uk/plat/time.h> // TODO: how does the build system find this path?

#include "helper_functions.h"

void create_remove_files(int file_amount);
void list_dir(int file_amount);

__nsec write_seq(BYTES bytes);
void write_seq_malloc(BYTES bytes);
void write_randomly(const char *filename, BYTES bytes, BYTES lower_write_limit, BYTES upper_write_limit);

void read_seq(BYTES bytes);
void read_seq_existing(const char *filename);
void read_randomly(const char *filename, BYTES bytes, BYTES lower_read_limit, BYTES upper_read_limit);

#endif
