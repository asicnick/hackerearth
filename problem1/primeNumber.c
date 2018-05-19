// primeNumber.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <math.h>


int main()
{
	int range;
	int flag;

	scanf("%d", &range);

	for (int i = 2; i <= range; i++) {
		flag = 0;

		// Reference: https://stackoverflow.com/questions/5811151/why-do-we-check-up-to-the-square-root-of-a-prime-number-to-determine-if-it-is-pr
		for (int j = 2; j <= (sqrt((double)range)); j++) {
			if ((i%j == 0) && (i != j)) {
				flag = 1; // 
			}

		}

		if (flag != 1)
			printf("%d ", i);
	}

	return 0;
}

