PROGRAM =	load
OBJS	=	parser.tab.o lex.yy.o load.o
SRCS	=	$(OBJS:%.o=%.c)
CFLAGS	=	-g -Wall
LDFLAGS	=
BISON	=	bison
BISONFLAGS	= -d
FLEX	=	flex

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
parser.tab.c: parser.y
	$(BISON) $(BISONFLAGS) parser.y
lex.yy.c: lexer.l	
	$(FLEX) $(FLEXFLAGS) lexer.l
	

clean:
	/bin/rm *.o parser.tab.c  parser.tab.h lex.yy.c load
