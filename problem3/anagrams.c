
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sort_string(char*, int*);
int get_difference(int*, int*);

int main() {
	int num_tests;
	char** ptest_strings;
	int str1_arr[27] = { 0 };
	int str2_arr[27] = { 0 };
	int *pstr1;
	int *pstr2;

	pstr1 = str1_arr;
	pstr2 = str2_arr;

	scanf("%d", &num_tests);
	ptest_strings = (char**)malloc((num_tests * 2) * 10000 * sizeof(char));

	for (int i = 0; i<num_tests * 2; i++) {
		scanf("%s", ptest_strings + i);
		if (i % 2 == 0) {
			sort_string((char*)(ptest_strings+i), pstr1);
		}
		else {
			sort_string((char*)(ptest_strings+i), pstr2);
			printf("%d\n", get_difference(pstr1, pstr2));
			memset(str1_arr, 0, sizeof(str1_arr));
			memset(str2_arr, 0, sizeof(str2_arr));
		}
	}

	free(ptest_strings);

	return 0;
}

// Get the difference between two strings.
int get_difference(int* str1_arr, int* str2_arr) {
	int acc = 0;
	int sub;
	for (int i = 0; i<27; i++) {
		sub = abs(str1_arr[i] - str2_arr[i]);
		if (sub != 0) {
			acc = acc + sub;
		}
	}
	return acc;
}

// Sort the input strings.
void sort_string(char* ptest_string_n, int* string_arr) {
	int idx;

	for (int i = 0; i<strlen(ptest_string_n); i++) {
		string_arr[(ptest_string_n[i] - 'a')]++;
	}

}