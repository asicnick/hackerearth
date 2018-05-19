// This one's for standard IO operations.
#include<stdio.h>
// This ones for malloc/free
#include<stdlib.h>
// This one's for memset
#include<string.h>


// Delcare the prototype of the function.
char* multiply(char* num1, char* num2);

// Entry point
int main() {

	int    num_elements;
	char* result;
	char p_num_in[5];

	// Get the number of elements we'll be multiplying.
	scanf("%d", &num_elements);

	// Allocate memory for storing the final result.
	// Assumption: Input will be in range from 0 to 10^3
	// Required Memory: 
	// If 2 numbers, 1000 x 1000 are multiplied, 
	// their result will occupy maximum 9 locations. 
	// So memory required = maximum 4.5 times per element. Rounding it to 5.
	result = (char*)malloc(sizeof(char)* (num_elements*5));

	// Initialize the result memory to 0. Optional step. Can get away
	// without it for this one. But keepint it still since it helps
	// debugging.
	memset(result, '0', (num_elements*5) * sizeof(char));
	

	// Main loop.
	// We'll not store all the elements before starting the operation.
    // Instead, as soon as we've 2 elements available, we'll start the
	// operation. The multiplication operation will be done in every
	// iteration after 2nd iteration.
	for (int i = 0; i < num_elements; i++) {
		if (i == 1) {                 
			scanf("%s", result);
		}
		else {
			scanf("%s", p_num_in);    
		}

		if (i>=1) // Start operation after 2nd iteration.
		  result = multiply(p_num_in, result);
	}

	// Print the result
	printf("%s", result);

	// Deallocate the result buffer. 
	// TODO: Fix this. Causing heap corruption.
	//free(result);

	return 0;
}

char* multiply(char* num1, char* num2) {
	char* tmp_result;
	char* mult_buf;
	int int_num1, int_num2;
	int len_num1, len_num2;
	int result;
	int carry;
	int j;
	int rc_i, rc_j;
	int real_size;

	// Get the length of both the strings.
	len_num1 = strlen(num1);
	len_num2 = strlen(num2);

	// Initialize the running count.
	rc_i = 0;
	rc_j = 0;

	// We alloc only enough memory to hold result which cannot exceed len_num1 + len_num2 + 1.
	// An extra +1 is for '\0' or string terminator character used by system to know where the
	// string ends.
	mult_buf = (char*)malloc(sizeof(char)*(len_num1+len_num2+1+1));

	// Initialize all the memory allocated above to 0. This is important step as we'll be
	// looking ahead in the memory while doing the operation. Anything other than 0 will 
	// result in unexpected answers.
	memset(mult_buf, '0', sizeof(char)*(len_num1+len_num2+1+1));

	// We'll start from the right most digit which is stored at the
	// highest location in the memory.
	for (int i = len_num1 - 1; i >= 0; i--) {
		// Since we're storing the number as character, the stored content is
		// infact the ASCII equivalent of the number. To get the actual number
		// in integer form, we subtracte the ASCII equivalent of 0.
		int_num1 = num1[i] - '0';
		
		// Initialize carry that may be generated in this iteration to 0.
		carry = 0;
		
		// Set running count of inner loop to 0.
		rc_j = 0;

		// Again start the multiplication from the right most digit which is stored at the
		// highest location in the memory.
		for (int j = len_num2 - 1; j >= 0; j--) {
			int_num2 = num2[j] - '0';

			// Eg: 31 x 15
			// Iteration:
			// i = 0; j = 0;
			// >> result = 1 * 5 + (0) - '0' + 0= 0
			// >> mult_buf[0+0] = 5 % 10 + '0' = 5
			// >> carry = 5/10 = 0

			// i = 0; j = 1;
			// >> result = 1 * 1 + (0) - '0' + 0 = 0
			// >> mult_buf[0+1] = 1 % 10 + '0' = 1
			// >> carry = 1/10 = 0

			// i = 1; j = 0;
			// >> result = 3 * 5 + (1) - '0' + 0 = 16
			// >> mult_buf[1+0] = 16 % 10 = 6
			// >> carry = 16/10 = 1

			// i = 1; j = 1;
			// >> result = 3 * 1 + (0) - '0' + 1 = 4
			// >> mult_buf[1+1] = 4 % 10 = 4
			// >> carry = 4/10 = 0;

			// End:
			// mult_buf[0] = 5
			// mult_buf[1] = 6
			// mult_buf[2] = 4
			result = int_num1 * int_num2 + ((mult_buf[rc_i + rc_j] - '0')) + carry;
			mult_buf[rc_i + rc_j] = (result % 10) + '0';
			carry = result / 10;

			rc_j++;
		}

		// Add any carry to the position that was generated in last iteration of j.
		if (carry>0)
			mult_buf[rc_i+rc_j] += carry;

		rc_i++;
	}

	// Ensure you terminate the string after all the operation is done
    // else garabage will appear in your result.
	mult_buf[rc_i + rc_j] = '\0';

	// Trim all the zeros before the actual result number.
	real_size = strlen(mult_buf)-1;

	while (real_size > 0 && mult_buf[real_size] == '0'+0)
		real_size--;


	// Allocate some memory for the final result. At this point we know exactly
	// how much memory is required by us.
	tmp_result = (char*)malloc(sizeof(char)*(real_size+1));
	memset(tmp_result, NULL, sizeof(char)*(real_size+1));

	// Since we stored our result in reverse order while computing,
	// reverse the order to get actual final result. This just a mere
	// swapping.
	j = 0;
	for (int i = real_size; i >= 0; i--) {
		tmp_result[j] = mult_buf[i];
		j++;
	}

	// Terminate the result string.
	tmp_result[real_size+1] = '\0';

	// Deallocate the memory for mult_buf
	free(mult_buf);

	// Return the result.
	return tmp_result;
}