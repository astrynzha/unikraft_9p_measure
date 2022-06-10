#ifndef MEASUREMENT_SCENARIOS_H
#define MEASUREMENT_SCENARIOS_H

#include <stdio.h>
#include <uk/plat/time.h>

#include "helper_functions.h"

__nsec create_files(int amount);
__nsec remove_files(int amount);
__nsec list_dir(int file_amount);

__nsec write_seq(BYTES bytes);
__nsec write_seq_malloc(BYTES bytes);
__nsec write_randomly(const char *filename, BYTES bytes, BYTES lower_write_limit, BYTES upper_write_limit);

__nsec read_seq(BYTES bytes);
__nsec read_seq_existing(const char *filename);
__nsec read_randomly(const char *filename, BYTES bytes, BYTES lower_read_limit, BYTES upper_read_limit);

#endif
