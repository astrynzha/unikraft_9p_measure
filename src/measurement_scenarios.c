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
#ifdef __Unikraft__
#include <uk/arch/lcpu.h>
#endif /* __Unikraft__ */

/*
    Measure removing `amount` files.

    Necessary files are created and deleted by the function.
*/
__nanosec create_files(FILES amount) {
	char dir_name[] = "create_files";
	mkdir(dir_name, 0777);
	int dir_fd = open(dir_name, O_RDONLY);
	chdir(dir_name);

	// initializing file names

	int max_file_name_length = 7 + DIGITS(amount - 1);
	char *file_names = (char*) malloc(amount*max_file_name_length); // 2D array
	init_filenames(amount, max_file_name_length, file_names);

	// measuring the creation of `amount` files

	__nanosec start, end;
	start = _clock();

	for (FILES i = 0; i < amount; i++) {

		int fd = open(file_names + i * max_file_name_length,
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
		if (fd == -1) {
			fprintf(stderr, "Error creating file number %lu.\n", i);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}

	fsync(dir_fd);

	end = _clock();

	// cleaning up: deleting all files

	for (FILES i = 0; i < amount; i++) {
		char *file_name = file_names + i * max_file_name_length;
		if (remove(file_name) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_name);
		}
	}
	chdir("..");
	close(dir_fd);
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

	// array of strings of size 256
	char *file_names = (char*) malloc(amount*256);
	char fname[256];
	for (FILES i = 0; i < amount; i++) {
		sprintf(fname, "%lu", i);
		strncpy(file_names + i*256, fname, 256);
	}

	// flush FS buffers and free pagecaches
	// #ifdef __linux__
	// system("sync; echo 3 > /proc/sys/vm/drop_caches");
	// #endif


	__nanosec start, end;
	start = _clock();
	for (FILES i = 0; i < amount; i++) {
		char *file_name = file_names + i * 256;
		if (unlink(file_name) != 0) {
			fprintf(stderr, "Failed to remove \"%s\" file\n", file_name);
		}
	}
	end = _clock();

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
	FILES file_count = 0;


	DIR *dp;
	struct dirent *ep;
	dp = opendir ("./");
	if (dp == NULL) {
			fprintf(stderr, "Couldn't open the directory\n");
	}

	start = _clock();

	while ( (ep = readdir (dp)) ) {
		file_count++;
	}

	end = _clock();

	(void) closedir (dp);

	assert(file_amount + 2 == file_count);

    return end - start;
}

#ifdef __Unikraft__
static inline size_t write_9p(int fd, char *buffer, BYTES buffer_size)
{
	BYTES rc;
	BYTES bytes_written = 0;
	size_t buff_limit_9p = 516096;

	BYTES iterations = buffer_size / buff_limit_9p;
	BYTES rest = buffer_size % buff_limit_9p;

	for (BYTES i = 0; i < iterations; i++) {
		rc = write(fd, buffer, buff_limit_9p);
		if (unlikely(rc != buff_limit_9p)) {
			fprintf(stderr, "Failed to write\n\
					rc = %llu\n\
					buffer = %lu\n",
					rc, buff_limit_9p);
		}
		bytes_written += rc;
	}
	if (rest > 0) {
		rc = write(fd, buffer, rest);
		if (unlikely(rc != rest)) {
			fprintf(stderr, "Failed to write the rest\n\
					rc = %llu\n\
					buffer = %llu\n",
					rc, rest);;
		}
		bytes_written += rc;
	}

	return bytes_written;
}

static inline size_t read_9p(int fd, char *buffer, BYTES buffer_size)
{
	BYTES rc;
	BYTES bytes_read = 0;
	size_t buff_limit_9p = 516096;

	BYTES iterations = buffer_size / buff_limit_9p;
	BYTES rest = buffer_size % buff_limit_9p;

	for (BYTES i = 0; i < iterations; i++) {
		rc = read(fd, buffer, buff_limit_9p);
		if (unlikely(rc != buff_limit_9p)) {
			fprintf(stderr, "Failed to read\n\
					rc = %llu\n\
					buffer = %lu\n",
					rc, buff_limit_9p);;
		}
		bytes_read += rc;
	}
	if (rest > 0) {
		rc = read(fd, buffer, rest);
		if (unlikely(rc != rest)) {
			fprintf(stderr, "Failed to read the rest\n\
					rc = %llu\n\
					buffer = %llu\n",
					rc, rest);;
		}
		bytes_read += rc;
	}

	return bytes_read;
}

#endif /* __Unikraft__ */

/*
    Measuring sequential write with buffer on heap, allocated with malloc.
	Buffer size can be set through 'buffer_size'.

    Write file is created and deleted by the function.
*/
__nanosec write_seq(int fd, BYTES bytes, BYTES buffer_size) {
	#ifdef __linux__
	BYTES rc;
	#endif /* __linux__ */

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
		#ifdef __linux__
		rc = write(fd, buffer, buffer_size);
		if (unlikely(rc != buffer_size)) {
			fprintf(stderr, "Failed to write\n");
		}
		#elif __Unikraft__
		write_9p(fd, buffer, buffer_size);
		#endif
	}
	if (rest > 0) {
		#ifdef __linux__
		rc = write(fd, buffer, rest);
		if (unlikely(rc != rest)) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
		#elif __Unikraft__
		write_9p(fd, buffer, rest);
		#endif
	}

	fsync(fd);

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

	#ifdef __linux__
	BYTES rc;
	#endif /* __linux__ */

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
			#ifdef __linux__
			rc = write(fd, buffer, buffer_size);
			if (unlikely(rc != buffer_size)) {
				fprintf(stderr, "Failed to write\n");
			}
			#elif __Unikraft__
			write_9p(fd, buffer, buffer_size);
			#endif
		}
		if (rest > 0) {
			#ifdef __linux__
			rc = write(fd, buffer, rest);
			if (unlikely(rc != rest)) {
				fprintf(stderr, "Failed to write the rest of the file\n");
			}
			#elif __Unikraft__
			write_9p(fd, buffer, rest);
			#endif
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
	#ifdef __linux__
	BYTES rc;
	#endif /* __linux__ */
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
		#ifdef __linux__
		rc = read(fd, buffer, buffer_size);
		if (unlikely(rc != buffer_size)) {
			fprintf(stderr, "Failed to write\n");
		}
		#elif __Unikraft__
		read_9p(fd, buffer, buffer_size);
		#endif
	}
	if (rest > 0) {
		#ifdef __linux__
		rc = read(fd, buffer, rest);
		if (unlikely(rc != rest)) {
			fprintf(stderr, "Failed to write the rest of the file\n");
		}
		#elif __Unikraft__
		read_9p(fd, buffer, rest);
		#endif
	}

	end = _clock();

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
	#ifdef __linux__
	BYTES rc;
	#endif /* __linux__ */
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

		BYTES iterations = len / buffer_size;
		BYTES rest = len % buffer_size;

		for (BYTES i = 0; i < iterations; i++) {
			#ifdef __linux__
			rc = read(fd, buffer, buffer_size);
			if (unlikely(rc != buffer_size)) {
				fprintf(stderr, "Failed to write\n");
			}
			#elif __Unikraft__
			read_9p(fd, buffer, buffer_size);
			#endif
		}
		if (rest > 0) {
			#ifdef __linux__
			rc = read(fd, buffer, rest);
			if (unlikely(rc != rest)) {
				fprintf(stderr, "Failed to write the rest of the file\n");
			}
			#elif __Unikraft__
			read_9p(fd, buffer, rest);
			#endif
		}
	}

	end = _clock();

	free(intervals);
	free(interval_order);
	free(buffer);
	return end - start;
}