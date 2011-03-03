#ifndef _STDI_H
#include <stdio.h>
#endif
#  include <stdlib.h>
#include <sys/types.h>
#include <utime.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"

void hoge_d(int a, const char *caller) {
	printf("in main : %d, %s\n", a, caller);
}

void fuga(void) {
	hoge(2);
}

int main() {
	puts("hello world!!");
	hoge(1);
	fuga();

	char *update_file;
	update_file = getenv("HOOKWRITE_UPDATE_FILE2");
	if (update_file) {
	    int fd;
	    fd = open(update_file, O_WRONLY|O_NONBLOCK|O_CREAT|O_NOCTTY, 0666);
	    close(fd);
	    utime(update_file, NULL);
	}

return 0;
}
