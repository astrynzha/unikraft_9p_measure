#include "scenario_runners.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#ifdef DEBUGMODE
#include <errno.h>
#include <string.h>
#endif // DEBUGMODE

#include "helper_functions.h"
#include "measurement_scenarios.h"
#include "time_functions.h"

void create_files_runner(FILES *amount_arr, size_t arr_size, int measurements) {

  // create a separate directory for this experiment

#ifdef __Unikraft__
  char dir_name[] = "create_files_unikraft";
#elif __linux__
  char dir_name[] = "create_files_linux";
#endif
  mkdir(dir_name, 0777);
  if (chdir(dir_name) == -1) {
    printf("Error: could not change directory to %s\n", dir_name);
  }

  char fname_results[] = "results.csv";
    FILE *fp_results = fopen(fname_results, "w");

    for (size_t i = 0; i < arr_size; i++) { // conducts measurement for each given amount of files
        char fname[17+DIGITS(i)];
        sprintf(fname, "measurement_%lu.csv", i);
        FILE *fp_measurement = fopen(fname, "w");

        FILES amount = amount_arr[i];
        printf("###########################\n");
        printf("%lu/%lu. Measuring creating %lu files\n", i+1, arr_size, amount);

        __nanosec result;
        __nanosec result_ms;
        __nanosec total = 0;

        // measures 'measurements' times, how long the creation 'amount' of files takes
        for (int i = 0; i < measurements; i++) {
            printf("    Measurement %d/%d running...\n", i + 1, measurements);

            result = create_files(amount);

            fprintf(fp_measurement, "%lu\n", result);
            result_ms = nanosec_to_milisec(result);
            printf("    Result: %lums %.3fs\n", result_ms, (double) result_ms / 1000);

            total += result;
        }

        total /= measurements;
        fprintf(fp_results, "%lu,%lu\n", amount, total);
        __nanosec total_ms = nanosec_to_milisec(total);

        printf("%d measurements successfully conducted\n", measurements);
        printf("Creating %lu files took on average: %lums %.3fs \n", amount, total_ms, (double) total_ms / 1000);

        fclose(fp_measurement);
    }

    fclose(fp_results);
    chdir("..");
}

void remove_files_runner(FILES *amount_arr, size_t arr_size, int measurements)
{
	int rc;

	// starting in /

	// create a separate directory for this experiment

	#ifdef __Unikraft__
	char dir_rm_dir[] = "remove_files_unikraft";
	#elif __linux__
	char dir_rm_dir[] = "remove_files_linux";
	#endif
	mkdir(dir_rm_dir, 0777);
	rc = chdir(dir_rm_dir);
	if (rc == -1) {
		printf("Error: could not change directory to %s\n", dir_rm_dir);
	}

	char fname_results[] = "results.csv";
	FILE *fp_results = fopen(fname_results, "w");

	char dname[256];

	for (size_t i = 0; i < arr_size; i++) {

		// in /remove_dir_unikraft

		char fname[17+DIGITS(i)];
		sprintf(fname, "measurement_%lu.csv", i);
		FILE *fp_measurement = fopen(fname, "w");
		rc = chdir("..");
		if (rc == -1) {
			printf("Error: could not change directory to %s\n", "..");
		}

		// in /

		FILES amount = amount_arr[i];

		printf("###########################\n");
		printf("%lu/%lu. Measuring removing %lu files\n", i+1, arr_size, amount);

		__nanosec result;
		__nanosec result_ms;
		__nanosec total = 0;

		for (int j = 0; j < measurements; j++) {
			sprintf(dname, "%lu_m%d", amount, j + 1);
			rc = chdir(dname);
			if (rc == -1) {
				printf("Error: could not change directory to"
				" %s\n", dname);
			}

			printf("Measurement %d/%d running...\n",
				j + 1, measurements);

			result = remove_files(amount);

			fprintf(fp_measurement, "%lu\n", result);
			result_ms = nanosec_to_milisec(result);
			printf("Result: %lums %.3fs\n", result_ms, (double) result_ms / 1000);

			total += result;

			rc = chdir("..");
			if (rc == -1) {
				printf("Error: could not change directory "
				"to %s\n", "..");
			}
		}

		// in /

		total /= measurements;
		fprintf(fp_results, "%lu,%lu\n", amount, total);
		__nanosec total_ms = nanosec_to_milisec(total);

		printf("%d measurements successfully conducted\n", measurements);
		printf("Removing %lu files took on average: %lums %.3fs \n", amount, total_ms, (double) total_ms / 1000);

		fclose(fp_measurement);

		// in /

		rc = chdir(dir_rm_dir);
		if (rc == -1) {
			printf("Error: could not change directory to %s\n", dir_rm_dir);
		}

		//in /remove_dir_unikraft
	}

	fclose(fp_results);
	chdir("..");
}

void list_dir_runner(FILES *amount_arr, size_t arr_size, int measurements)
{
	int rc;

	// starting in /
	// create outer directory

	#ifdef __Unikraft__
	char dir_list_dir[] = "list_dir_unikraft";
	#elif __linux__
	char dir_list_dir[] = "list_dir_linux";
	#endif
	mkdir(dir_list_dir, 0777);
	rc = chdir(dir_list_dir);
	if (rc == -1) {
		printf("Error: could not change directory to %s\n", dir_list_dir);
	}

	// file for mean

	char fname_results[] = "results.csv";
	FILE *fp_results = fopen(fname_results, "w");

	char dname[256];

	for (size_t i = 0; i < arr_size; i++) {

		//in /list_dir_unikraft

		// directory for files to create and list in

		char fname[17+DIGITS(i)];
		sprintf(fname, "measurement_%lu.csv", i);
		FILE *fp_measurement = fopen(fname, "w");
		rc = chdir("..");
		if (rc == -1) {
			printf("Error: could not change directory to %s\n", "..");
		}

		// in /

		FILES file_amount = amount_arr[i];


		printf("###########################\n");
		printf("%lu/%lu. Measuring listing %lu files\n", i+1,
			arr_size, file_amount);

		__nanosec result;
		__nanosec result_ms;
		__nanosec total = 0;

		for (int j = 0; j < measurements; j++) {
			sprintf(dname, "%lu_m%d", file_amount, j + 1);
			rc = chdir(dname);
			if (rc == -1) {
				printf("Error: could not change directory to"
				" %s\n", dname);
			}

			// #ifdef __linux__
			// system("sync; echo 3 > /proc/sys/vm/drop_caches");
			// #endif

			printf("Measurement %d/%d running...\n",
				j + 1, measurements);

			result = list_dir(file_amount);

			fprintf(fp_measurement, "%lu\n", result);
			result_ms = nanosec_to_milisec(result);
			printf("Result: %lums %.3fs\n",
				result_ms, (double) result_ms / 1000);

			total += result;

			rc = chdir("..");
			if (rc == -1) {
				printf("Error: could not change directory "
				"to %s\n", "..");
			}
		}

		// in /

		total /= measurements;
		fprintf(fp_results, "%lu,%lu\n", file_amount, total);
		__nanosec total_ms = nanosec_to_milisec(total);

		printf("%d measurements successfully conducted\n", measurements);
		printf("Listing %lu files took on average: %lums %.3fs \n", file_amount, total_ms, (double) total_ms / 1000);

		fclose(fp_measurement);

		// in /

		rc = chdir(dir_list_dir);
		if (rc == -1) {
			printf("Error: could not change directory to %s\n", dir_list_dir);
		}

		//in /list_dir_unikraft
	}

    fclose(fp_results);
    chdir("..");
}

void write_seq_runner(const char *filename, BYTES *bytes_arr, BYTES *buffer_size_arr, size_t arr_size,
		      int measurements)
{
	int fd = open(filename, O_WRONLY);
	if (fd == -1) {
		fprintf(stderr, "Error opening file 'write_data'.\n");
		exit(EXIT_FAILURE);
	}


    // create a separate directory for this experiment

    #ifdef __Unikraft__
    char dir_name[] = "write_seq_unikraft";
    #elif __linux__
    char dir_name[] = "write_seq_linux";
    #endif
    mkdir(dir_name, 0777);
    if (chdir(dir_name) == -1) {
        printf("Error: could not change directory to %s\n", dir_name);
    }

    char fname_results[] = "results.csv";
    FILE *fp_results = fopen(fname_results, "w");

    for (size_t i = 0; i < arr_size; i++) { // conducts measurement for each buffer_size
        char fname[17+DIGITS(i)];
        sprintf(fname, "measurement_%lu.csv", i);
        FILE *fp_measurement = fopen(fname, "w");

        BYTES buffer_size = buffer_size_arr[i];
	BYTES bytes = bytes_arr[i];

        printf("###########################\n");
		printf("%lu/%lu. Sequential write.\n\
		Megaytes: %llu,\n\
		Buffer_size: %lluB\n",
		i+1, arr_size, B_TO_MB(bytes), buffer_size);


        __nanosec result;
        __nanosec result_ms;
        __nanosec total = 0;

        for (int i = 0; i < measurements; i++) {
		#ifdef __linux__
		system("sync; echo 3 > /proc/sys/vm/drop_caches");
		#endif

		printf("Measurement %d/%d running...\n", i + 1, measurements);

		result = write_seq(fd, bytes, buffer_size);
		lseek(fd, 0, SEEK_SET);

		fprintf(fp_measurement, "%lu\n", result);
		result_ms = nanosec_to_milisec(result);
		printf("Result: %lums %.3fs\n", result_ms, (double) result_ms / 1000);

		total += result;
	}

        total /= measurements;
        fprintf(fp_results, "%llu,%lu\n", buffer_size, total);
        __nanosec total_ms = nanosec_to_milisec(total);

        printf("%d measurements successfully conducted\n", measurements);
        printf("Average result: %lums %.3fs \n", total_ms, (double) total_ms / 1000);

        fclose(fp_measurement);
    }

    fclose(fp_results);
	close(fd);
    chdir("..");
}

void write_randomly_runner(const char *filename, BYTES *bytes_arr,
	BYTES *buffer_size_arr, BYTES *interval_len_arr, size_t arr_size,
	int measurements)
{
	int fd = open(filename, O_WRONLY);
	if (fd == -1) {
		fprintf(stderr, "Error opening file 'write_data'.\n");
		exit(EXIT_FAILURE);
	}

    // create a separate directory for this experiment

    #ifdef __Unikraft__
    char dir_name[] = "write_rand_unikraft";
    #elif __linux__
    char dir_name[] = "write_rand_linux";
    #endif
    mkdir(dir_name, 0777);
    if (chdir(dir_name) == -1) {
        printf("Error: could not change directory to %s\n", dir_name);
    }

  char fname_results[] = "results.csv";
  FILE *fp_results = fopen(fname_results, "w");

    for (size_t i = 0; i < arr_size; i++) { // conducts measurement for each buffer_size
        char fname[17+DIGITS(i)];
        sprintf(fname, "measurement_%lu.csv", i);
        FILE *fp_measurement = fopen(fname, "w");

        BYTES buffer_size = buffer_size_arr[i];
	BYTES bytes = bytes_arr[i];
	BYTES interval_len = interval_len_arr[i];

	printf("###########################\n");
		printf("%lu/%lu. Random write.\n\
		Megaytes: %llu,\n\
		Buffer_size: %lluB\n\
		Interval_length: %llu\n",
		i+1, arr_size, B_TO_MB(bytes), buffer_size, interval_len);

        printf("###########################\n");
        printf("%lu/%lu. Measuring random write of %llu megabytes with a buffer of %lluB\n",
            i+1, arr_size, B_TO_MB(bytes), buffer_size);

        __nanosec result;
        __nanosec result_ms;
        __nanosec total = 0;

        for (int i = 0; i < measurements; i++) {
		#ifdef __linux__
		system("sync; echo 3 > /proc/sys/vm/drop_caches");
		#endif

		printf("Measurement %d/%d running...\n", i + 1, measurements);

		srand(time(NULL)); // setting random seed
		result = write_randomly(fd, bytes, buffer_size, interval_len);

		fprintf(fp_measurement, "%lu\n", result);
		result_ms = nanosec_to_milisec(result);
		printf("Result: %lums %.3fs\n", result_ms, (double) result_ms / 1000);

		total += result;
        }

        total /= measurements;
        fprintf(fp_results, "%llu,%lu\n", buffer_size, total);
        __nanosec total_ms = nanosec_to_milisec(total);

        printf("%d measurements successfully conducted\n", measurements);
        printf("Writing %llu non-sequentially took on average: %lums %.3fs \n",
            B_TO_MB(bytes), total_ms, (double) total_ms / 1000);

        fclose(fp_measurement);
    }

    fclose(fp_results);
	close(fd);
    chdir("..");
}

/*
    'bytes' has to be less than file size.
*/
void read_seq_runner(const char *filename, BYTES *bytes_arr,
    BYTES *buffer_size_arr, size_t arr_size, int measurements) {

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error opening file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    // create a separate directory for this experiment

    #ifdef __Unikraft__
    char dir_name[] = "read_seq_unikraft";
    #elif __linux__
    char dir_name[] = "read_seq_linux";
    #endif
    mkdir(dir_name, 0777);
    if (chdir(dir_name) == -1) {
        printf("Error: could not change directory to %s\n", dir_name);
    }

    char fname_results[] = "results.csv";
    FILE *fp_results = fopen(fname_results, "w");

    for (size_t i = 0; i < arr_size; i++) { // conducts measurement for each buffer_size
        char fname[17+DIGITS(i)];
        sprintf(fname, "measurement_%lu.csv", i);
        FILE *fp_measurement = fopen(fname, "w");

        BYTES buffer_size = buffer_size_arr[i];
	BYTES bytes = bytes_arr[i];

        printf("###########################\n");
        printf("###########################\n");
		printf("%lu/%lu. Sequential read.\n\
		Megaytes: %llu,\n\
		Buffer_size: %lluB\n",
		i+1, arr_size, B_TO_MB(bytes), buffer_size);

        __nanosec result;
        __nanosec result_ms;
        __nanosec total = 0;

        for (int i = 0; i < measurements; i++) {
            #ifdef __linux__
            system("sync; echo 3 > /proc/sys/vm/drop_caches");
            #endif
            printf("Measurement %d/%d running...\n", i + 1, measurements);

            result = read_seq(fd, bytes, buffer_size);
	    lseek(fd, 0, SEEK_SET);

            fprintf(fp_measurement, "%lu\n", result);
            result_ms = nanosec_to_milisec(result);
            printf("Result: %lums %.3fs\n", result_ms, (double) result_ms / 1000);

            total += result;
        }

        total /= measurements;
        fprintf(fp_results, "%llu,%lu\n", buffer_size, total);
        __nanosec total_ms = nanosec_to_milisec(total);

        printf("%d measurements successfully conducted\n", measurements);
        printf("Reading %lluMB with %lluB buffer took on average: %lums %.3fs \n", B_TO_MB(bytes), buffer_size, total_ms, (double) total_ms / 1000);

        fclose(fp_measurement);
    }

    fclose(fp_results);
    close(fd);
    chdir("..");
}

void read_randomly_runner(const char *filename, BYTES *bytes_arr,
			  BYTES *buffer_size_arr, BYTES *interval_len_arr,
			  size_t arr_size, int measurements)
{
	// FILE *file;
	// file = fopen(filename, "r");
	// if (file == NULL) {
	// 	fprintf(stderr, "Error opening file '%s'.\n", filename);
	// 	exit(EXIT_FAILURE);
	// }

	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Error opening file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

    // create a separate directory for this experiment

    #ifdef __Unikraft__
    char dir_name[] = "read_rand_unikraft";
    #elif __linux__
    char dir_name[] = "read_rand_linux";
    #endif
    mkdir(dir_name, 0777);
    if (chdir(dir_name) == -1) {
        printf("Error: could not change directory to %s\n", dir_name);
    }

    char fname_results[] = "results.csv";
    FILE *fp_results = fopen(fname_results, "w");

    for (size_t i = 0; i < arr_size; i++) { // conducts measurement for each buffer_size
        char fname[17+DIGITS(i)];
        sprintf(fname, "measurement_%lu.csv", i);
        FILE *fp_measurement = fopen(fname, "w");

        BYTES buffer_size = buffer_size_arr[i];
	BYTES bytes = bytes_arr[i];
	BYTES interval_len = interval_len_arr[i];

	printf("###########################\n");
		printf("%lu/%lu. Random read.\n\
		Megaytes: %llu,\n\
		Buffer_size: %lluB\n\
		Interval_length: %llu\n",
		i+1, arr_size, B_TO_MB(bytes), buffer_size, interval_len);

        __nanosec result;
        __nanosec result_ms;
        __nanosec total = 0;

        for (int i = 0; i < measurements; i++) {
            #ifdef __linux__
            system("sync; echo 3 > /proc/sys/vm/drop_caches");
            #endif
            printf("Measurement %d/%d running...\n", i + 1, measurements);

            srand(time(NULL)); // setting random seed
            result = read_randomly(fd, bytes, buffer_size, interval_len);

            fprintf(fp_measurement, "%lu\n", result);
            result_ms = nanosec_to_milisec(result);
            printf("Result: %lums %.3fs\n", result_ms, (double) result_ms / 1000);

            total += result;
        }

        total /= measurements;
        fprintf(fp_results, "%llu,%lu\n", buffer_size, total);
        __nanosec total_ms = nanosec_to_milisec(total);

        printf("%d measurements successfully conducted\n", measurements);
        printf("Reading %lluMB with a buffer of %lluB took on average: %lums %.3fs \n",
            B_TO_MB(bytes), buffer_size, total_ms, (double) total_ms / 1000);

        fclose(fp_measurement);
    }

    fclose(fp_results);
	close(fd);
    chdir("..");
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