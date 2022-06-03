#include "scenario_runners.h"

#include <uk/plat/time.h> // TODO: how does the build system find this path?

#include <time.h>
#include <stdlib.h>

#include "helper_functions.h"
#include "measurement_scenarios.h"

/*
    Creates a file, filled with 'X' charachters, of size `bytes`, with a given filename
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

void write_seq_runner(BYTES bytes, int measurements) {
    __nsec total = 0;

    printf("###########################\n");
    printf("Measuring sequential write\n");

    __nsec result;
    __nsec result_ms;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i, measurements);

        result = write_seq(bytes);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Writing %llu megabytes took on average: %ldms %.3fs \n", B_TO_MB(bytes), total_ms, (double) total_ms / 1000);
}

void write_seq_malloc_runner(BYTES bytes, int measurements) {
    __nsec total = 0;
    printf("###########################\n");
    printf("Measuring sequential write with malloc\n");

    __nsec result;
    __nsec result_ms;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i, measurements);

        result = write_seq_malloc(bytes);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Writing %llu with malloc megabytes took on average: %ldms %.3fs \n", B_TO_MB(bytes), total_ms, (double) total_ms / 1000);
}

void write_randomly_runner(const char *filename, BYTES bytes, BYTES lower_write_limit, BYTES upper_write_limit, int measurements) {
    __nsec total = 0;
    printf("###########################\n");
    printf("Measuring random-access write\n");

    __nsec result;
    __nsec result_ms;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i, measurements);

        srand(time(NULL));
        result = write_randomly(filename, bytes, lower_write_limit, upper_write_limit);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Writing %llu non-sequentially took on average: %ldms %.3fs \n", B_TO_MB(bytes), total_ms, (double) total_ms / 1000);
}

void read_seq_runner(BYTES bytes, int measurements) {
    __nsec total = 0;

    printf("###########################\n");
    printf("Measuring sequential read\n");

    __nsec result;
    __nsec result_ms;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i, measurements);

        result = read_seq(bytes);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Reading %llu megabytes took on average: %ldms %.3fs \n", B_TO_MB(bytes), total_ms, (double) total_ms / 1000);
}

void read_seq_existing_runner(const char *filename, int measurements) {
    __nsec total = 0;

    FILE *file = fopen(filename, "r");
    BYTES size = get_file_size(file);
    fclose(file);

    printf("###########################\n");
    printf("Measuring sequential read of %lluMB\n", B_TO_MB(size));

    __nsec result;
    __nsec result_ms;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i, measurements);

        result = read_seq_existing(filename);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Reading %llu megabytes took on average: %ldms %.3fs \n", B_TO_MB(size), total_ms, (double) total_ms / 1000);
}

void read_randomly_runner(const char *filename, BYTES bytes, BYTES lower_read_limit, BYTES upper_read_limit, int measurements) {
    // TODO: set srand
    __nsec total = 0;

    printf("###########################\n");
    printf("Measuring random-access read\n");

    __nsec result;
    __nsec result_ms;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i, measurements);

        srand(time(NULL));
        result = read_randomly(filename, bytes, lower_read_limit, upper_read_limit);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Reading %llu megabytes took on average: %ldms %.3fs \n", B_TO_MB(bytes), total_ms, (double) total_ms / 1000);

}

