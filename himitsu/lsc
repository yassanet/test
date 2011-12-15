#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>

int option_l = 0;
int option_a = 0;

struct node {
	char path[1024];
	struct stat *buf;
	struct node *next;
};

struct list {
	struct node *head;
	int size;
};

struct node *getnode_ite(struct list *l, int *num) {
	struct node *n;
	int i;

	n = l->head;
	for(i = 0; i < l->size; i++) {
		if(i == *num) {
			(*num)++;
			return n;
		}
		n = n->next;
	}
	return NULL;
}

struct node *newnode(char *name, int size) {
	struct node *n;
	n = malloc(sizeof(struct node));
	n->buf = malloc(sizeof(struct stat));
	memcpy(n->path, name, size);
	n->next = NULL;

	return n;
}

int append(struct list *list, struct node *n) {
	int i;

	if(!list || !n)
		return -1;	
	if(list->head == NULL) {
		list->head = n;
		list->size++;
		return 0;
	}

	struct node *next;
	next = list->head;
	for(i = 0; i < list->size; i++) {
		if(next->next == NULL) {
			next->next = n;
			list->size++;
			return 0;
		} else {
			next = next->next;
		}
	}
	return -2;	
}

void appendbypath(struct list *l, char *path, int size) {
	struct node *n;
	n = newnode(path, size);
	append(l, n);
}

void printlist(struct list l) {
	struct node *n;
	int i;
	n = l.head;

	for(i = 0; i < l.size; i++) {
		if(n != NULL) {
			printf("%s\n", n->path);
			n = n->next;
		} else {
			break;
		}
	}
}

void freelist(struct list l) {
	struct node *n;
	int i;
	n = l.head;

	for(i = 0; i < l.size; i++) {
		if(n != NULL) {
			n = n->next;
		} else {
			break;
		}
	}
}

void usage() {
	fprintf(stdout, "usage: Illegal option\n");
	fprintf(stdout, "ls [-la] [file ...]\n");
}

void printargs(int argc, char *argv[]) {

	int i = 0;
	
	for(i = 0; i < argc; i++) {
		fprintf(stdout, "%s\n", argv[i]);
	}
}

void print_fileinfo(const char *name, struct stat buf, int invisible) {
	char time[25];
	struct passwd *pw;

	if(invisible != 1 && !strncmp(name, ".", 1)) {
		return;
	}

	pw = getpwuid(buf.st_uid);
	fprintf(stdout, "%o\t%d\t%s\t%d\t%d", 
			buf.st_mode, buf.st_nlink, pw->pw_name, 
			buf.st_gid, buf.st_size
		);
	memcpy(time, (char *)ctime(&buf.st_mtime), 24);

	if(S_ISLNK(buf.st_mode)) {	//symbolic link
		char *rpath;
		rpath = realpath(name, NULL);
		fprintf(stdout, "\t%s\t%s -> %s\n", time, name, rpath);
	} else {
		fprintf(stdout, "\t%s\t%s\n", time, name);
	}
}

int main(int argc, char *argv[]) {

	int n;
	extern char *optarg;		/* for getopt */
	extern int optind, opterr;	/* for getopt */

	option_l = 0;
	option_a = 0;
	
	while((n = getopt(argc, argv, "la")) != -1) {
		switch(n) {
		case 'l':
			option_l = 1;
			break;
		case 'a':
			option_a = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	struct list list;
	list.head = NULL;
	list.size = 0;
	int num;
	for(num = 0; num < argc; num++) {
		appendbypath(&list, argv[num], 1023);
	}

	int iterator = 0;
	struct node *node;
	DIR *dir;
	struct dirent *dirent;
	// check file type and print.
	while( (node = getnode_ite(&list, &iterator)) != NULL) {
		if(lstat(node->path, node->buf) != 0) {
			perror("lstat");
		}
		if(S_ISDIR(node->buf->st_mode)) {	// dir
			//if(strncmp(dirent->d_name, "/", 1)) {
			fprintf(stdout, "%s:\n", node->path);
			dir = opendir(node->path);
			struct stat *buf;
			buf = malloc(sizeof(struct stat));
			while( (dirent = readdir(dir)) != NULL) {
				memset(buf, 0, sizeof(buf));
				if(option_l == 1) {
					char path[1024];
					memcpy(path, node->path, strlen(node->path));
			fprintf(stdout, "%s:%d:%d\n", path, strlen(path), strlen(node->path));
			fprintf(stdout, "%s\n", path[1]);
					if(strncmp(&path[strlen(node->path) - 1], "/", 1)) {
						strcat(path, "/");
					}
					strcat(path, dirent->d_name);
					if(lstat(path, buf) != 0) 
						perror("lstat");
					print_fileinfo(dirent->d_name, *buf, option_a);
				} else {
					fprintf(stdout, "%s\n", dirent->d_name);	
				}
			}
			closedir(dir);
		} else if(S_ISLNK(node->buf->st_mode)) {	//symbolic link
			if(option_a != 1 && !strncmp(dirent->d_name, ".", 1)) {
			} else {
				char *rpath;
				rpath = realpath(node->path, NULL);
				char time[25];
				struct passwd *pw;
				// get username by passwd
				pw = getpwuid(node->buf->st_uid);
				fprintf(stdout, "%o\t%d\t%s\t%d\t%d", 
						node->buf->st_mode, node->buf->st_nlink, pw->pw_name, 
						node->buf->st_gid, node->buf->st_size
					);
				memcpy(time, (char *)ctime(&node->buf->st_mtime), 24);
				fprintf(stdout, "\t%s\t%s -> %s\n", time, node->path, rpath);

				free(rpath);
			}
		} else {	//regular file
			if(option_l == 1) {
				char time[25];
				struct passwd *pw;
				// get username by passwd
				pw = getpwuid(node->buf->st_uid);
				fprintf(stdout, "%o\t%d\t%s\t%d\t%d", 
						node->buf->st_mode, node->buf->st_nlink, pw->pw_name, 
						node->buf->st_gid, node->buf->st_size
					);
				memcpy(time, (char *)ctime(&node->buf->st_mtime), 24);
				fprintf(stdout, "\t%s\t%s\n", time, node->path);
			} else {
				fprintf(stdout, "%s\n", node->path);	
			}
		}
		fprintf(stdout, "\n");
	}

	return 0;
}
