#ifndef MEASUREMENT_SCENARIOS_H
#define MEASUREMENT_SCENARIOS_H

#include <stdio.h>

#include "helper_functions.h"
#include "time_functions.h"

__nanosec create_files(FILES amount);
__nanosec remove_files(FILES amount);
__nanosec list_dir(FILES file_amount);

__nanosec write_seq(int fd, BYTES bytes, BYTES buffer_size);
__nanosec write_randomly(int fd, BYTES size, BYTES buffer_size,
			 BYTES interval_len);

__nanosec read_seq(int fd, BYTES bytes, BYTES buffer_size);
__nanosec read_randomly(int fd, BYTES size, BYTES buffer_size,
			BYTES interval_len);

#endif
