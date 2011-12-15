#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "himitsu.h"

void usage() {
	fprintf(stdout, "usage: \n");
}

int main(int argc, char *argv[]) {
	char file[256];
	int mode = 0;

	int n;
	extern char *optarg;		/* for getopt */
	extern int optind, opterr;	/* for getopt */

	while ((n = getopt (argc, argv, "p:sf:")) != -1) {
		switch (n) {
		case 's':	/* save text and password */
			fprintf(stdout, "opt s\n");
			mode = 1;
			break;
		case 'f': /* set password to file */
			fprintf(stdout, "opt f\n");
			memcpy(file, optarg, 255);
			mode = 2;
			break;
		case 'p': /* output file */
			fprintf(stdout, "opt p\n");
			memcpy(file, optarg, 255);
			mode = 3;
			break;
		default:
			usage();
		}
	}

	for(; optind < argc; optind++) {
		printf("arg = %s\n", argv[optind]);
	}

	if(mode == 1) {
		create_secrettext();
	} else if(mode == 2) {
		struct stat st;
		if(stat(file, &st) != 0) {
			fprintf(stdout, "%s dosen't exist\n", file);
		} else if(S_ISDIR(st.st_mode)){
			fprintf(stdout, "%s is dir\n", file);
		} else if(S_ISREG(st.st_mode)) {
			set_passwd_tofile(file);
		}
	} else if(mode == 3) {
		struct stat st;
		if(stat(file, &st) != 0) {
			fprintf(stdout, "%s dosen't exist\n", file);
		} else if(S_ISDIR(st.st_mode)){
			fprintf(stdout, "%s is dir\n", file);
		} else if(S_ISREG(st.st_mode)) {
			decode_file(file);
		}
	}


	return 0;
}
