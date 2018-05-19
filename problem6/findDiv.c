// findDiv.cpp : Defines the entry point for the console application.
//

#include "stdio.h"


int main()
{
	unsigned int l;
	unsigned int r;
	unsigned int k;
	unsigned int start;
	unsigned int div_count;

	scanf("%u", &l);
	scanf("%u", &r);
	scanf("%u", &k);

	start = l;
	div_count = 0;

	while (start <= r){
		div_count += ((start%k) == 0);
		start++;
	}

	printf("%u", div_count);

	return 0;
}

