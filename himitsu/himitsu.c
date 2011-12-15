#define _XOPEN_SOURCE	//must first
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "himitsu.h"

char passwdfile[] = "./passwd";

struct termio tty, tty_save;
int passwd_len = 10;

void create_secrettext(void) {
	printf("create_secrettext\n");
}

void set_passwd_tofile(char *file) {
	char passwd[passwd_len+1];
	char *hashpasswd = NULL;
	FILE *f = NULL;

	if(save_passwd(passwd, passwd_len, 1) == 0) {
		hashpasswd = hash_passwd(passwd, hashpasswd);
		if(hashpasswd == NULL)
			fprintf(stdout, "error hash\n");
	}

	//encode for openssl command
	/*
	char command[256];
	sprintf(command, "/usr/bin/openssl des-ede3 -e -base64 -k '%s' -in %s -out %s.en", passwd, file, file);
	system(command);
	*/

	//decode for openssl command
	/*
	memcpy(command, "\0", 255);
	sprintf(command, "/usr/bin/openssl des-ede3 -d -base64 -k '%s' -in %s.en -out %s.de", passwd, file, file);
	system(command);
	*/

	/* put hash password. */
	f = fopen(passwdfile, "a+");
	if(f == NULL)
		return;

	fprintf(f, "%s %s\n", file, hashpasswd);
	fclose(f);

	free(hashpasswd);
}

void decode_file(char *file) {
	char passwd[passwd_len+1];
	char *hashpasswd = NULL;
	char yourpwd[256];

	if(save_passwd(passwd, passwd_len, 0) == 0) {
		hashpasswd = hash_passwd(passwd, hashpasswd);
		if(hashpasswd == NULL)
			fprintf(stdout, "error hash\n");
	}
	if(search_passwd(yourpwd, file) <= 0) {
		fprintf(stdout, "not found password\n");
		return;
	}
	if(strcmp(hashpasswd, yourpwd) == 0) {
		FILE *f = fopen(file, "r");
		if(f == NULL)
			return;

		int n = 0;
		char buf[1024];
		while( (n = fread(buf, sizeof(char), 1024, f)) != 0 ) {
			fprintf(stdout, "%s", buf);
		}
		fclose(f);
	} else {
		fprintf(stdout, "different password.\n");
	}

	free(hashpasswd);
}

char *hash_passwd(char *pwd, char *hashpasswd) {
	char salt[] = "$1$aa$";

	return crypt(pwd, salt);
}

int search_passwd(char *pwd, char *key) {

	FILE *f = NULL;
	f = fopen(passwdfile, "r");
	if(f == NULL) {
		fprintf(stdout, "cannot open file.\n");
		return -1;
	}

	char tmp1[256]; char tmp2[256];
	int ret;

	while( ( ret = fscanf( f, "%[^ ] %s\n", tmp1, tmp2) ) != EOF ) {
		if(strcmp(tmp1, key) == 0) {
			memcpy(pwd, tmp2, 256);
			fclose(f);
			return 1;
		}
	}
	fprintf(stdout, "not found entry.\n");

	fclose(f);

	return 0;
}

int save_passwd(char *pwd, int pwd_len, int again) {

	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= ECHO;
	tty.c_lflag |= ECHONL;
	ioctl(0, TCSETAF, &tty);

	fprintf(stdout, "passwd = ");
	myfgets(pwd, pwd_len+1);

	if(again == 1) {
		char pwd_again[pwd_len+1];
		fprintf(stdout, "again = ");
		myfgets(pwd_again, pwd_len+1);

		if(strncmp(pwd, pwd_again, pwd_len)) {
			fprintf(stderr, "no match passwd. exit.");
			return -1;
		}
	}

	closing();

	return 0;
}

void closing(void) {
	ioctl(0, TCSETAF, &tty_save);
}
