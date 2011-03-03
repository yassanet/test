%{
#include <stdio.h>
extern int yylex(void);
extern FILE *yyin;
extern char g_program_name[80];
extern char g_library[80];
extern char g_threadnum[80];
#ifdef __x86_64__
#define YYSTYPE_IS_DECLARED 1
typedef long long YYSTYPE;
#endif

int
yywrap(void)
{
	return (1);
}

void
yyerror(const char *msg)
{
	(void) fprintf(stderr, "%s\n", msg);
}
%}

%token		T_LIBRARY
%token		T_THREADNUM
%token		T_STRING
%token		T_NUM
%token		L_EQ
%token		L_QUOTE
%token		L_OPEN_PAREN
%token		L_CLOSE_PAREN
%token		L_SEMICOLON

%%
configration
	:T_STRING L_OPEN_PAREN statements L_CLOSE_PAREN {
		(void) snprintf(g_program_name, sizeof(g_program_name), "%s", (char *) $1);
		free((char *) $1);
	};

statement
	: library_statement
	| threadnum_statement
	;

statements
	: statement
	| statements statement
	;

library_statement
	: T_LIBRARY L_EQ L_QUOTE T_STRING L_QUOTE L_SEMICOLON {
		(void) snprintf(g_library, sizeof(g_library), "%s", (char *) $4);
		free((char *) $4);
	};

threadnum_statement
	: T_THREADNUM L_EQ T_NUM L_SEMICOLON {
		(void) snprintf(g_threadnum, sizeof(g_threadnum), "%d", (int) $3);
	}
	| T_THREADNUM L_EQ L_QUOTE T_STRING L_QUOTE L_SEMICOLON {
		(void) snprintf(g_threadnum, sizeof(g_threadnum), "%s", (char *) $4);
		free((char *) $4);
	};
