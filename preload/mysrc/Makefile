PROGRAM =	main
CFLAGS	=	-g -Wall
LDFLAGS	=
CC		=	gcc

all: libhookputs main

libhookputs: libhookputs.o
	$(CC) -shared -W1,-soname,libhookputs.so -ldl -o libhookputs.so libhookputs.o
libhookputs.o: libhookputs.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c libhookputs.c

libhookwrite: libhookwrite.o
	$(CC) -shared -W1,-soname,libhookwrite.so -ldl -o libhookwrite.so libhookwrite.o
libhookwrite.o: libhookwrite.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c libhookwrite.c

$(PROGRAM): main.c main.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o main main.c

clean:
	/bin/rm *.o *.so main
