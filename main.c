#include <stdio.h>
#include <stdlib.h>
#include <uk/plat/time.h> // TODO: where is this path defined?

int main(void)
{
	FILE *in;
	char buffer[128];

	__nsec start,end, time_s;

	start = ukplat_monotonic_clock();

	in = fopen("/grass", "rt");
	if (in == NULL) {
		fprintf(stderr, "Error opening file '/green'.");
		exit(EXIT_FAILURE);
	}
	fgets(buffer, 128, in);
	printf("File contents: %s\n", buffer);
	fclose(in);

	end = ukplat_monotonic_clock();

	time_s = ukarch_time_nsec_to_msec(end - start);

	printf("%ld %ld\n", end-start, time_s);

	printf("Bye, world!\n");

	return 0;
}
