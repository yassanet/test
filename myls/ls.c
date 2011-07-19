#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

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
	//dir
	while( (node = getnode_ite(&list, &iterator)) != NULL) {
		if(lstat(node->path, node->buf) != 0) {
			perror("lstat");
		}
		if(S_ISDIR(node->buf->st_mode)) {
			fprintf(stdout, "%s:\n", node->path);
			dir = opendir(node->path);
			struct stat *buf;
			buf = malloc(sizeof(struct stat));
			while( (dirent = readdir(dir)) != NULL) {
				memset(buf, 0, sizeof(buf));
				if(option_a != 1 && option_l != 1) {
					if( strncmp(dirent->d_name, ".", 1)) {
						fprintf(stdout, "%s\n", dirent->d_name);	
					}
				} else if(option_a != 1 && option_l == 1) {
					if( strncmp(dirent->d_name, ".", 1)) {
						char path[1024];
						memcpy(path, node->path, 1024);
						strcat(path, dirent->d_name);
						if(lstat(path, buf) != 0) 
							perror("lstat");
						fprintf(stdout, "%o %d %d %d %d", 
								buf->st_mode, buf->st_nlink, buf->st_uid, 
								buf->st_gid, buf->st_size
							);
						fprintf(stdout, " %s %s\n", ctime(&buf->st_mtime), dirent->d_name);
					}
				} else if(option_a == 1 && option_l != 1) {
					fprintf(stdout, "%s\n", dirent->d_name);	
				} else if(option_a == 1 && option_l == 1) {
					if( strncmp(dirent->d_name, ".", 1)) {
						char *path = strcat(node->path, dirent->d_name);
						lstat(path, buf);
						fprintf(stdout, "0%3o%s\n", buf->st_mode, dirent->d_name);	
					}
				}	
			}
			closedir(dir);
		} else {
			fprintf(stdout, "%s\n", node->path);
		}
		fprintf(stdout, "\n");
	}

	return 0;
}
