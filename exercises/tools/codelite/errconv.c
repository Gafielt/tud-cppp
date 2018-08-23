/**
 * @file conv.c
 *
 * @brief
 *
 * @author Laurenz Kamp <laurenz.kamp@gmx.de>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char buf[1024];
	char file[256];
	int line;
	char type;
	int ret = 0;

	do {
		if(fgets(buf, 1024, stdin) == NULL) {
			break;
		}

		if(strncmp(buf, "***", 3) == 0) {
			int i;
			char *t = buf;

			t += 4; // Skip "*** ".
			for(i = 0; *t != '('; i++, t++) {
				file[i] = *t;
			}
			file[i] = '\0';

			t++; // Skip '('.
			line = atoi(t);

			while(*t != ' ') {
				t++;
			}

			type = t[1];

			while(*t != ':') {
				t++;
			}
			t += 2;

			printf("%s:%d:0: %s: %s", file, line, (type == 'E' ? "error" : "warning"), t);

			if(type == 'E') {
				ret = -1;
			}
		}
	} while (!feof(stdin));

	return ret;
}

