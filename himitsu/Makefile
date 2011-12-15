#
# Makefile 
#

PROGRAM = himitsu
C_FILES = main.c himitsu.c
CFLAGS += -g -Wall
INCLUDE =
LIBPATH =
CC = gcc

all:$(PROGRAM)

clean:
	rm -f $(PROGRAM)
	rm -f *.o

depend:
	makedepend --$(CFLAGS) --$(INCLUDE) --$(LIBPATH) --$(C_FILES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) -c $< -o $@

$(PROGRAM):$(C_FILES:.c.o)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) -o $@ $(C_FILES:.c.o)

# DO NOT DELETE

himitsu.o: /usr/include/stdio.h /usr/include/features.h
himitsu.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
himitsu.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
himitsu.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
himitsu.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
himitsu.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
himitsu.o: himitsu.h /usr/include/openssl/md5.h /usr/include/openssl/e_os2.h
himitsu.o: /usr/include/openssl/opensslconf.h
himitsu.o: /usr/include/openssl/opensslconf-x86_64.h
