#include "measurement_scenarios.h"
#include "helper_functions.h"
#include "time_functions.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
    Measure removing `amount` files.

    Necessary files are created and deleted by the function.
*/
__nanosec create_files(FILES amount) {
	char dir_name[] = "create_files";
	mkdir(dir_name, 0777);
	chdir(dir_name);

	// initializing file names

    int max_file_name_length = 7 + DIGITS(amount - 1);
	char *file_names = (char*) malloc(amount*max_file_name_length); // 2D array
	init_filenames(amount, max_file_name_length, file_names);

    // measuring the creation of `amount` files

	__nanosec start, end;
	start = _clock();

	for (FILES i = 0; i < amount; i++) {
		FILE *file = fopen(file_names + i * max_file_name_length, "w");
	    if (file == NULL) {
            fprintf(stderr, "Error creating file number %lu.\n", i);
            exit(EXIT_FAILURE);
        }
		#ifdef __linux__
		int fd = fileno(file);
		fsync(fd);
		#endif
		fclose(file);
	}

	end = _clock();

    // cleaning up: deleting all files

	for (FILES i = 0; i < amount; i++) {
		char *file_name = file_names + i * max_file_name_length;
		if (remove(file_name) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_name);
		}
	}
    chdir("..");
    int ret = rmdir(dir_name);
    if (ret == -1) {
        printf("Failed to remove directory %s\n", dir_name);
    }

	free(file_names);

    return end - start;
}

/*
    Measure creating `amount` files.

    Necessary files are created and deleted by the function.
*/
__nanosec remove_files(FILES amount) {
	char dir_name[] = "remove_files";
	mkdir(dir_name, 0777);
	chdir(dir_name);

	// initializing file names

    int max_file_name_length = 7 + DIGITS(amount - 1);
	char *file_names = (char*) malloc(amount*max_file_name_length); // 2D array
	init_filenames(amount, max_file_name_length, file_names);

    // creating `amount` empty files

	for (FILES i = 0; i < amount; i++) {
		FILE *file = fopen(file_names + i*max_file_name_length, "w");
	    if (file == NULL) {
            fprintf(stderr, "Error creating file number %lu.\n", i);
            exit(EXIT_FAILURE);
        }
		fclose(file);
	}

	// flush FS buffers and free pagecaches
	#ifdef __linux__
	system("sync; echo 3 > /proc/sys/vm/drop_caches");
	#endif

    // measuring the delition of `amount` files

    __nanosec start, end;
	start = _clock();
	for (FILES i = 0; i < amount; i++) {
		char *file_name = file_names + i * max_file_name_length;
		if (remove(file_name) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_name);
		}
		#ifdef __linux__
		sync();
		#endif
	}
	end = _clock();

    chdir("..");
    int ret = rmdir(dir_name);
    if (ret == -1) {
        printf("Failed to remove directory %s\n", dir_name);
    }

	free(file_names);

    return end - start;
}

/*
    Measure listing (e.g. ls command) of files. 'file_amount'
	specifies how many files are in the directory.

    Necessary files are to be created and deleted by the caller
*/
__nanosec list_dir(FILES file_amount) {
	__nanosec start, end;

	start = _clock();

	DIR *dp;
	struct dirent *ep;
	dp = opendir ("./");
    if (dp == NULL) {
		fprintf(stderr, "Couldn't open the directory\n");
    }

	char str[256];
	#ifdef DEBUGMODE
	FILES file_count = 0;
	#endif
    while ( (ep = readdir (dp)) ) {
		strcpy(str, ep->d_name); // using filenames somehow
		#ifdef DEBUGMODE
		file_count++;
		#endif
    }
    (void) closedir (dp);

	end = _clock();

	#ifdef DEBUGMODE
	assert(file_amount + 2 == file_count);
	#endif

    return end - start;
}

/*
    Measuring sequential write with buffer on heap, allocated with malloc.
	Buffer size can be set through 'buffer_size'.

    Write file is created and deleted by the function.
*/
__nanosec write_seq(int fd, BYTES bytes, BYTES buffer_size) {
	long long rc;

	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated.\n");
		exit(0);
	}
	BYTES iterations = bytes / buffer_size;
	BYTES rest = bytes % buffer_size;

	__nanosec start, end;
	start = _clock();

	for (BYTES i = 0; i < iterations; i++) {
		rc = write(fd, buffer, buffer_size);
		if (rc == -1) {
			fprintf(stderr, "Failed to write\n");
		}
	}
	if (rest > 0) {
		rc = write(fd, buffer, rest);
		if (rc == -1) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
	}

	/* TODO: should I measure with the fsync? */
	// fsync(fd);

	end = _clock();

	free(buffer);

    return end - start;
}

/*
    Measuring random access write (non-sequential) of an existing file, passed to the function.
    Seed has to be set by the caller.


    The function:
    1. Randomly determines a file position from range [0, EOF - upper_write_limit).
    2. Writes a random amount of bytes, sampled from range [lower_write_limit, upper_write_limit].
    3. Repeats steps 1-2 until the 'remaining_bytes' amount of bytes is written.
*/
__nanosec write_randomly(int fd, BYTES size, BYTES buffer_size,
			 BYTES interval_len)
{
	struct file_interval *intervals;
	BYTES *interval_order;
	BYTES num_intervals;

	slice_file(size, &intervals,
		&interval_order, &num_intervals,
		interval_len);

	long long rc;

	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated. At %s, line %d. \n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	memset(buffer, '1', buffer_size);
	buffer[buffer_size - 1] = '\0';

	BYTES off;
	BYTES len;

	__nanosec start, end;
	start = _clock();

	for (BYTES i = 0; i < num_intervals; i++) {
		off = intervals[interval_order[i]].off;
		len = intervals[interval_order[i]].len;
		lseek(fd, off, SEEK_SET);

		BYTES iterations = len / buffer_size;
		BYTES rest = len % buffer_size;

		for (BYTES j = 0; j < iterations; j++) {
			rc = write(fd, buffer, buffer_size);
			if (rc == -1) {
				fprintf(stderr, "Failed to write\n");
			}
		}
		if (rest > 0) {
			rc = write(fd, buffer, rest);
			if (rc == -1) {
				fprintf(stderr, "Failed to write the rest of the file\n");
			}
		}
	}

	fsync(fd);

	end = _clock();

	free(buffer);
	free(intervals);
	free(interval_order);
	return end - start;
}

/*
    Measure sequential read of `bytes` bytes.
*/
__nanosec read_seq(int fd, BYTES bytes, BYTES buffer_size)
{
	long long rc;
	BYTES iterations = bytes / buffer_size;
	BYTES rest = bytes % buffer_size;

	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated. At %s, line %d. \n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	__nanosec start, end;

	start = _clock();

	for (BYTES i = 0; i < iterations; i++) {
		rc = read(fd, buffer, buffer_size);
		if (rc == -1) {
			fprintf(stderr, "errno: %s\n",
				strerror(errno));
			fprintf(stderr,
			"Failed to read on iteration #%llu\n", i);
			start = end = 0;
			goto out;
		}

		// if (buffer_size != fread(buffer, sizeof(char), buffer_size, file)) {
		// 	fprintf(stderr, "Failed to read on iteration #%llu\n", i);
		// }
	}
	if (rest > 0) {
		rc = read(fd, buffer, rest);
		if (rc == -1) {
			fprintf(stderr,
			"Failed to read the rest of the file\n");
			start = end = 0;
			goto out;
		}
		// if (rest != fread(buffer, sizeof(char), rest, file)) {
		// 	fprintf(stderr, "Failed to read the rest of the file\n");
		// }
	}

	// fsync(fd);

	end = _clock();

out:
	free(buffer);
	return end - start;
}


/*
    Measuring random access read (non-sequential). Seed has to be set by the caller.

    The function:
    1. Randomly determines a file position from range [0, EOF - upper_read_limit).
    2. Reads a random amount of bytes, sampled from range [lower_read_limit, upper_read_limit].
    3. Repeats steps 1-2 until the 'remeaning_bytes' amount of bytes is read.

    File is provided by the caller.
*/
__nanosec read_randomly(int fd, BYTES size, BYTES buffer_size,
			BYTES interval_len)
{
	struct file_interval *intervals;
	BYTES *interval_order;
	BYTES num_intervals;

	slice_file(size, &intervals,
		&interval_order, &num_intervals,
		interval_len);

	__nanosec start, end;
	BYTES off;
	BYTES len;

	char *buffer = malloc(buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error! Memory not allocated. At %s, line %d. \n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	start = _clock();

	for (BYTES i = 0; i < num_intervals; i++) {
		off = intervals[interval_order[i]].off;
		len = intervals[interval_order[i]].len;
		lseek(fd, off, SEEK_SET);
		// read_bytes(fd, len, buffer_size, buffer);

		long long rc;
		BYTES iterations = len / buffer_size;
		BYTES rest = len % buffer_size;

		for (BYTES i = 0; i < iterations; i++) {
			rc = read(fd, buffer, buffer_size);
			if (rc == -1) {
				puts("Failed to read\n");
			}
		}
		if (rest > 0) {
			rc = read(fd, buffer, rest);
			if (rc == -1) {
				puts("Failed to read\n");
			}
		}
	}

	end = _clock();

	free(intervals);
	free(interval_order);
	free(buffer);
	return end - start;
}