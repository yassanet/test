#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int myfgets(char *, int);

int main(void) {

	char s1[10];
	char s2[10];

	myfgets(s1, 10);
	printf("get = \"%s\"", s1);

	myfgets(s2, 10);
	printf("get = \"%s\"", s2);

	return 0;
}

/*
  remove '\n' and odd char.
*/
int myfgets(char *s, int len) {
	int n;

	if (fgets(s, len, stdin) == NULL)
	/* エラー処理 */;
	n = strlen(s);
	//printf("input = \"%s\"", s);
	//printf("next getchar = \"%c\"", getchar());
	if (s[n - 1] == '\n')
	{
		s[n - 1] = '\0';
	}
	else
	{
		int c;
		do
		{
			c = getchar();
			if (c == EOF)
			{
				if (feof(stdin))
					break;
				else
				/* エラー処理 */;
			}
		}
		while (c != '\n');
	}
	//printf("input = \"%s\"", s);

	return 0;
}
