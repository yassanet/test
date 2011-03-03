#include <stdio.h>
#include <string.h>

extern int yyparse(void);
extern FILE *yyin;
char g_program_name[80];
char g_library[80];
char g_threadnum[80];

int 
main(int argc, char *argv[]) {
	char fname[80], *ptr;

	if((ptr = strrchr(argv[0], '/')) == NULL) {
			ptr = argv[0];
	} else {
		ptr++;
	}
	/* open configure file */
	(void) snprintf(fname, sizeof(fname), "%s.conf", ptr);
	if((yyin = fopen(fname, "r")) == NULL) {
		(void) fprintf(stderr, "Cannot open %s\n", fname);
		return(-1);
	}
	/* read configure file */
	if(yyparse() != 0) {
		(void) fprintf(stderr, "Cannot read %s\n", fname);
		(void) fclose(yyin);
		return(-1);
	}
	(void) fclose(yyin);
	/* check program name */
	if(strcmp(ptr, g_program_name) != 0) {
		(void) fprintf(stderr, "Configuration not found for %s\n", ptr);
		return(-1);
	}

	printf("load library = %s\n", g_library);
	printf("load threadnum= %s\n", g_threadnum);

	return 0;
}
