#ifndef MEASUREMENT_SCENARIOS_H
#define MEASUREMENT_SCENARIOS_H

#include <stdio.h>
#include <uk/plat/time.h>

#include "helper_functions.h"

__nsec create_files(FILES amount);
__nsec remove_files(FILES amount);
__nsec list_dir(FILES file_amount);

__nsec write_seq(BYTES bytes, BYTES buffer_size);
__nsec write_randomly(FILE *file, BYTES bytes, BYTES buffer_size, BYTES lower_write_limit, BYTES upper_write_limit);

__nsec read_seq(FILE *file, BYTES bytes);
__nsec read_seq_existing(FILE *file);
__nsec read_randomly(FILE *file, BYTES bytes, BYTES lower_read_limit, BYTES upper_read_limit);

#endif
