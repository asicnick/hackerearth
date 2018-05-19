
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_reverse_in_place(char *str, int len);

int main() {
	char in_str[101];
	char rev_str[101];
	char* p_rev_str;
	char* p_in_str;

	scanf("%s", in_str);

	p_in_str = in_str;
	p_rev_str = rev_str;

	strcpy(p_rev_str, p_in_str);

	p_rev_str = str_reverse_in_place(p_rev_str, strlen(p_rev_str));

	if (!(*p_rev_str - *p_in_str))
		printf("%s", "YES");
	else
		printf("%s", "NO");

	return 0;
}


char *str_reverse_in_place(char *str, int len)
{
	char *p1 = str;
	char *p2 = str + len - 1;

	while (p1 < p2) {
		char tmp = *p1;
		*p1++ = *p2;
		*p2-- = tmp;
	}

	return str;
}