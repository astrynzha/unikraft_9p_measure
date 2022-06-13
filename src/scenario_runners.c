#include "scenario_runners.h"

#include <uk/plat/time.h>

#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>


#include "helper_functions.h"
#include "measurement_scenarios.h"


void create_files_runner(FILES amount, int measurements) {
    printf("###########################\n");
    printf("Measuring creating %lu files\n", amount);

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        result = create_files(amount);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Creating %lu files took on average: %ldms %.3fs \n", amount, total_ms, (double) total_ms / 1000);
}

void remove_files_runner(FILES amount, int measurements) {
    printf("###########################\n");
    printf("Measuring removing %lu files\n", amount);

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        result = remove_files(amount);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Removing %lu files took on average: %ldms %.3fs \n", amount, total_ms, (double) total_ms / 1000);
}

void list_dir_runner(FILES file_amount, int measurements) {
    char dir_name[] = "list_dir";
    mkdir(dir_name, 0777);
    chdir(dir_name);

    // initializing files 

    int max_file_name_length = 7 + DIGITS(file_amount - 1);
	char *file_names = (char*) malloc(file_amount*max_file_name_length); // implicit 2D array
	init_filenames(file_amount, max_file_name_length, file_names);

	for (FILES i = 0; i < file_amount; i++) {
        create_file_of_size(file_names + i*max_file_name_length, 0);
	}

    // measuring 

    printf("###########################\n");
    printf("Measuring listing %lu files\n", file_amount);

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;


    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        result = list_dir(file_amount);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Listing %lu files took on average: %ldms %.3fs \n", file_amount, total_ms, (double) total_ms / 1000);

    // deleting all created files and directories

	for (FILES i = 0; i < file_amount; i++) {
		if (remove(file_names + i*max_file_name_length) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_names + i*max_file_name_length);
		}
	}
    chdir("/..");
    rmdir(dir_name);
}

void write_seq_runner(BYTES bytes, BYTES buffer_size, int measurements) {
    printf("###########################\n");
    printf("Measuring sequential write of %llu megabytes with a buffer of %lluB\n", B_TO_MB(bytes), buffer_size);

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        result = write_seq(bytes, buffer_size);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Average result: %ldms %.3fs \n", total_ms, (double) total_ms / 1000);
}

void write_randomly_runner(const char *filename, BYTES bytes, BYTES buffer_size, BYTES lower_write_limit, BYTES upper_write_limit, int measurements) {
	FILE *file;
	file = fopen(filename, "r+");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

    printf("###########################\n");
    printf("Measuring random-access write\n");

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        srand(time(NULL)); // setting random seed
        result = write_randomly(file, bytes, buffer_size, lower_write_limit, upper_write_limit);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Writing %llu non-sequentially took on average: %ldms %.3fs \n", B_TO_MB(bytes), total_ms, (double) total_ms / 1000);

	fclose(file);
}

/*
    'bytes' has to be less than file size.
*/
void read_seq_runner(const char *filename, BYTES bytes, BYTES buffer_size, int measurements) {
    FILE *file = fopen(filename, "r");

    printf("###########################\n");
    printf("Measuring sequential read\n");

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        // TODO: flush cache
        rewind(file);
        result = read_seq(file, bytes, buffer_size);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);
    printf("%d measurements successfully conducted\n", measurements);
	printf("Reading %lluMB with %lluB buffer took on average: %ldms %.3fs \n", B_TO_MB(bytes), buffer_size, total_ms, (double) total_ms / 1000);
}

void read_seq_existing_runner(const char *filename, int measurements) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
    }

    printf("###########################\n");
    printf("Measuring sequential read of %lluMB\n", B_TO_MB(get_file_size(file)));

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        result = read_seq_existing(file);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Reading %llu megabytes took on average: %ldms %.3fs \n", B_TO_MB(get_file_size(file)), total_ms, (double) total_ms / 1000);

    fclose(file);
}

void read_randomly_runner(const char *filename, BYTES bytes, BYTES buffer_size, BYTES lower_read_limit, BYTES upper_read_limit, int measurements) {
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

    printf("###########################\n");
    printf("Measuring random-access read\n");

    __nsec result;
    __nsec result_ms;
    __nsec total = 0;

    for (int i = 0; i < measurements; i++) {
        printf("Measurement %d/%d running...\n", i + 1, measurements);

        srand(time(NULL)); // setting random seed
        result = read_randomly(file, bytes, buffer_size, lower_read_limit, upper_read_limit);
        result_ms = ukarch_time_nsec_to_msec(result); 
        printf("Result: %ldms %.3fs\n", result_ms, (double) result_ms / 1000);

        total += result;
    }

    total /= measurements;
    __nsec total_ms = ukarch_time_nsec_to_msec(total);

    printf("%d measurements successfully conducted\n", measurements);
	printf("Reading %lluMB with a buffer of %lluB took on average: %ldms %.3fs \n", 
        B_TO_MB(bytes), buffer_size, total_ms, (double) total_ms / 1000);

	fclose(file);
}

/*
    Creates a file, filled with 'X' charachters, of size `bytes`, with a given filename
*/
FILE *create_file_of_size(const char *filename, BYTES bytes) {
	FILE *file;
	BYTES buffer_size = KB(1);
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

    // TODO: surround with debug guards
	// printf("File %s of size %lluB created\n", filename, bytes);

	return file;
}