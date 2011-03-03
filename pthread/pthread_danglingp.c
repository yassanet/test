#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

struct str2 {
	char b[10];
};

struct str1 {
	int a;
	char b[10];
	struct str2 *str2;
};

pid_t gettid(void)
{
    return (pid_t)syscall(224);
}

void* thread_main( void* args )
{
	printf("IN THREAD : thread_id(self) = %X\n", pthread_self()); 
	printf("IN THREAD : thread_id(pid) = %d\n", getpid()); 
	printf("IN THREAD : thread_id(tid) ps -eLf = %d\n", gettid()); 

	struct str1 *h;
	h = args;
	printf("IN THREAD : h' address = %X\n", h);
//	  memset(&h, args, sizeof(struct str1));
//	  h=*args;
	sleep(10);	/* now, args(str1) is dead */
	printf("IN THREAD : str1 a=%d, b=%s\n", h->a, h->b);	/* dead pointer access */
	printf("IN THREAD : str2 b=%s\n", h->str2->b);	/* dead pointer access */

	return NULL;
}

int jjj(struct str1 *h) {
	printf("jjj");
	sleep(2);
	h->a = 3;
	memcpy(h->b, "str12", 10);	
	memcpy(h->str2->b, "str22", 10);	
		
	printf("		str1 a=%d, b=%s\n", h->a, h->b);
	printf("		str2 b=%s\n", h->str2->b);
}

int main()
{
	printf("IN MAIN : thread_id(self) = %X\n", pthread_self()); 
	printf("IN MAIN : thread_id(pid) = %d\n", getpid()); 
	printf("IN MAIN : thread_id(tid) ps -eLf = %d\n", gettid()); 

	int i;
	struct str1 *h;
	struct str2 *f;

	h = malloc(sizeof(struct str1));
	f = malloc(sizeof(struct str2));

	h->a = 2;
	memcpy(h->b, "str11", 10);	
	printf("str1 a=%d, b=%s\n", h->a, h->b);
	h->str2 = f;
	memcpy(f->b, "str21", 10);	
	printf("str2 b=%s\n", h->str2->b);

	pthread_t thread;
	for( i=0; i<1; ++i ){
		pthread_create( &thread, NULL, thread_main, (void *)h );
	}
	if(h) {
		printf("free h\n");
		free(h);
		h=NULL; /* defend dangling pointer*/
	}
	if(f) {
		printf("free f\n");
		free(f);
		f=NULL;
	}

	printf("wait pthread\n");
	pthread_join( thread, NULL );
	sleep(5);
	fprintf( stderr, "end mainthread\n" );

	return 0;
}

