#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myio.h"

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
