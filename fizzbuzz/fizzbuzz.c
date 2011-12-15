#include <stdio.h>

int main(int argc, char *argv[]) {
	int num = 0;
	extern char *optarg;            /* for getopt */
	extern int optind, opterr;      /* for getopt */

	while ((n = getopt (argc, argv, "n:")) != -1) {
		switch (n) {
		case 'n':       /* save text and password */
			num = atoi(optarg);
			if(num <= 0) {
				fprintf(stderr, "more than 0\n");	
			}
			break;
		case default:

		}
	}

	int i = 0;
	for(i = 0; i <= num; i++) {
		if(num % 3 == 0) {
			fprintf(stdout, "fizz");
		} else if(num )
	}
}
