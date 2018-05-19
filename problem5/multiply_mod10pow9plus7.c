// multiplyMod10_9_p7.cpp : Defines the entry point for the console application.
//

#include "stdio.h"


int main()
{
	unsigned int num_elements;
	unsigned int num1;
	unsigned int num_result;

	scanf("%d", &num_elements);

	for (int i = 0; i < num_elements; i++) {
		if (i == 1) {
			scanf("%d", &num_result);
		}
		else {
			scanf("%d", &num1);
		}

		if (i>=1) {
			num_result = (num1*num_result) % (1000000007);
		}
	}

	printf("%d", num_result);

	return 0;
}

