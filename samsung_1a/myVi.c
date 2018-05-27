#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myVi.h"


int main() {
	char* copy_buffer = NULL;
	char** general_buffer = NULL;

	command_interpreter(general_buffer, copy_buffer);

	return 0;
}

int command_interpreter(char** general_buffer, char* copy_buffer) {

	// Input string. Constraints T <= 1100 characters.
	char input_str[1100];

	// This is a dynamic table which will store the pointers of memory
	// where text line is stored. 
	// line_table[0] = 0th line, line_table[1] = 1st line and so on...
	char**  line_table;

	// Number of Inputs.
	int  num_inp;

	// Number of Queries.
	int  num_queries = 0;

	// Size of query. Can never be more than 4. Extra 1 for string termination.
	char query[5];

	// Internal variable to grab the status after executing the query.
	int query_response = 1;

	// Position of the pointer within the text. Mostly will point the end of line.
	int position = 0;

	// Pointer to point the current selected line.
	int buf_ptr = 0;

	// Size of the current buffer. This reflects the number of VALID elements currently
	// present in the buffer.
	int cur_buf_size = 0;

	// Used while copy-paste operation. 
	// After every copy, valid_paste will be 1.
	// After every paste, valid_paste will be 0.
	int valid_paste = 0;

	// We're allocating memory in blocks of 20 chunks. This tell how many such blocks are
	// allocated. Note that this is just storage for address of 20 chunks. Actual chunks
	// may not be necessarily allocated.
	int cur_alloc_blocks = 0;

	// Total number of chunks actually in use.
	int total_memory_chunks = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Get the number of inputs.
	scanf("%d", &num_inp);

	// Allocate memory for storing pointers of lines.
	// Allocating maximum memory i.e. 100 pointers for 100 lines as per sepcification.
	// TODO: Can be optimized to dynamically size this table.
	line_table = (char**)malloc(sizeof(char*)* MAX_LINES);


	// Get number of blocks required based on the inputs.
	// 1 block = 20 lines of texts.
	cur_alloc_blocks = get_blocks(num_inp);

	// Allocating blocks according to number of initial text inputs.
	// This will store the pointers to the memory where actual data is stored.
	general_buffer = (char**)malloc(sizeof(char*)*cur_alloc_blocks);

	// Initialze current buffer size to 0.
	cur_buf_size = 0;
	
	// Get the initial input text.
	for (int i = 0; i < num_inp; i++){
		// The [^\n] is required to allow white spaces in the input string.
		scanf(" %[^\n]s", input_str);

		// Allocate the memory for actual text input.
		// This will only allocate enough memory required for current input texts.
		general_buffer[i] = (char*)malloc(sizeof(char)*MAX_TEXT_SIZE);

		// Copy the input string to main buffer.
		memcpy(general_buffer[i], (char*)input_str, sizeof(char)*strlen(input_str)+1);

		// Update the line table with the pointer of respective line.
		line_table[buf_ptr] = general_buffer[buf_ptr];

		// Update the position to the end of current line.
		position = strlen(input_str);

		// Increment buf pointer, current buffer size and total memory chunks.
		buf_ptr++;
		cur_buf_size++;
		total_memory_chunks++;
	}

	// At the end, decrement the buf pointer, so we point to the last VALID line.
	buf_ptr--;


	// Get the number of queries.
	scanf("%d", &num_queries);

	// Processing the queries.
	for (int i = 0; i < num_queries; i++) {
		scanf("%s", query);

		// Insert
		if ((!(strcmp("i", query)))) {
			scanf("%d", &num_inp);

			// If insertion requires more memory than we allocated previously, we'll need to allocate more memory.
			if (get_blocks(cur_buf_size + num_inp) > cur_alloc_blocks) {
				cur_alloc_blocks = get_blocks(cur_buf_size + num_inp);
				general_buffer = (char**)realloc(general_buffer, sizeof(char*)* cur_alloc_blocks);
			}

			// Get the input text given by insertion command.
			for (int j = 0; j < num_inp; j++) {
				scanf(" %[^\n]s", input_str);
				
				// Allocate more chunks if required. This is different from above allocation. The above allocation is for
				// more blocks. 
				if (buf_ptr+1 > total_memory_chunks) {
					buf_ptr++;
					general_buffer[j + buf_ptr -1] = (char*)malloc(sizeof(char)*MAX_TEXT_SIZE);
					memcpy(general_buffer[j + buf_ptr-1], (char*)input_str, sizeof(char)*strlen(input_str) + 1);
					line_table[buf_ptr] = general_buffer[buf_ptr];
					total_memory_chunks++;
				}
				else {
					// If lines were deleted, we can reuse that memory to store new lines.
					// Here we find the location from which data was deleted.
					if (buf_ptr + 1 > cur_buf_size)
					  line_table[buf_ptr] = findMemory(line_table, general_buffer, total_memory_chunks);

					// Run the insert query.
					query_response = insert_str(line_table, input_str, &buf_ptr, position);

					// Increment the buffer pointer and set the position to start of next line.
					buf_ptr++;
					position = 0;
				}

				// If we inserted a new line, we increment the current buffer size.
				// If we just appended to existing line, we don't increment.
				if (buf_ptr>cur_buf_size)
				  cur_buf_size++;
			}

			buf_ptr--;
		}

		// Delete
		else if ((!(strcmp("dd", query)))) {
			query_response = delete_str(general_buffer, &buf_ptr, &position, &cur_buf_size, line_table);
		}

		// Copy and Delete
		else if ((!(strcmp("dy", query)))) {
			copy_buffer = (char*)malloc(sizeof(char)*(strlen(general_buffer[buf_ptr]) + 1));
			query_response = copy_str(general_buffer, copy_buffer, buf_ptr, &valid_paste);
			query_response = delete_str(general_buffer, &buf_ptr, &position, &cur_buf_size, line_table);
		}

		// Copy
		else if ((!(strcmp("y", query)))) {
			copy_buffer = (char*)malloc(sizeof(char)*(strlen(general_buffer[buf_ptr]) + 1));
			query_response = copy_str(general_buffer, copy_buffer, buf_ptr, &valid_paste);
		}

		// Move cursor
		else if (strstr(query, ":")) {
			query[0] = '0';
			buf_ptr = 0;
			for (int z = 0; z<strlen(query); z++){
				buf_ptr = buf_ptr * 10 + (query[z] - '0');
			}
			buf_ptr--;

			query_response = move_cur(line_table, &buf_ptr, &position);
		}

		// Paste
		else if ((!(strcmp("p", query)))) {
			query_response = paste_str(general_buffer, copy_buffer, buf_ptr, &position, &valid_paste);
		}
		else {
			// Invalid command. Ideally should never come here as per the problem statement.
			// This is a custom enhancement.
			// We'll wait until we get num_queries of VALID COMMANDS and won't consider invalid commands
			// as part of num_queries count.
			// Can put a print here but that will be too much deflecting from actual problem.
			i--;
		}
	}

	query_response = print(line_table, &cur_buf_size);

	//TODO: Fix the memory deallocation.
	for (int i = 0; i < cur_buf_size; i++)
		free(general_buffer[i]);

	for (int i = 0; i < 100; i++)
		free(line_table[i]);


	return 0;

}

// Get block count.
int get_blocks(int num_ins) {
	int div;
	int mod;
	int  s_num;
    
	div = num_ins / MIN_BLOCK_SIZE;
	mod = num_ins % MIN_BLOCK_SIZE;

	if (mod > 0)
		return div + 1;
	else
		return div;

}


// Insert query
int insert_str(char** line_table, char* text2insert, int* buf_ptr, int position){

	// We start inserting the text from a particular position.
	// Position = 0, if we're inserting a new line.
	// Position = end of existing line, if we're appending to the exisiting line.

	// TODO: We can just do a memcpy while inserting new line. Will improve performance
	// as opposed to copying character by character.
	for (int i = position; i < position + strlen(text2insert) + 1; i++) {
		line_table[*buf_ptr][i] = text2insert[i-position];
	}


	return 0;
}


// Delete query
int delete_str(char** general_buffer, int* buf_ptr, int* position, int* cur_buf_size, char** line_table) {

	// Set the content of location to be deleted to NULL.
	memset(general_buffer[*buf_ptr], NULL , strlen(general_buffer[*buf_ptr]));

	// Decrement current buffer size.
	if (*cur_buf_size > 0){
		(*cur_buf_size)--;
	}

	// Update the line_table to remove the deleted line and re-arrange the pointers.
	update_table(line_table, *buf_ptr, *cur_buf_size);

	// Decrement the buf pointer if the deleted line is the last line.
	if (*cur_buf_size == *buf_ptr && *buf_ptr != 0) {
		(*buf_ptr)--;
	}

	// Set the position to last character of the line currently pointed by buf pointer.
	move_cur(line_table, buf_ptr, position);	

	return 0;
}


// Copy string.
int copy_str(char** general_buffer, char* copy_buffer, int buf_ptr, int* valid_paste){
	memcpy(copy_buffer, general_buffer[buf_ptr], (strlen(general_buffer[buf_ptr]) + 1)*sizeof(char));
	*valid_paste = 1;
	return 0;
}

// Paste string.
int paste_str(char** general_buffer, char* copy_buffer, int buf_ptr, int* position, int* valid_paste) {

	if (*valid_paste) {
	  for (int i = *position; i < strlen(copy_buffer) + *position + 1; i++) {
		  general_buffer[buf_ptr][i] = copy_buffer[i - *position];
	  }
	  *position = strlen(general_buffer[buf_ptr]);
	  *valid_paste = 0;

	  free(copy_buffer);
	  return 0;
    }


	return 1;
}

// Move cursor
int move_cur(char** line_table, int* buf_ptr, int* position) {
	if (line_table[*buf_ptr] != NULL)
		*position = strlen((line_table[*buf_ptr]));
	else
		*position = 0;

	return 0;
}

// Print the final output.
int print(char** line_table , int* cur_buf_size) {
	for (int i = 0; i < *cur_buf_size; i++) {
		printf("%s\n", line_table[i]);
	}

	return 0;
}

// Update the line table.
int update_table(char** line_table, int deleted_line, int cur_buf_size) {

	// We remove the pointer of the deleted line and shift all pointers,
	// one location up.
	for (int i = deleted_line; i < cur_buf_size; i++) {
		line_table[i] = line_table[i + 1];
	}

	// Set the last location to NULL.
	line_table[cur_buf_size] = NULL;

	return 0;
}

// Find memory in general buffer to reuse it for inserting another string.
char* findMemory(char** line_table, char** general_buffer, int total_chunks) {
	char** all_mem;
	char* found_mem;

	// We traverse the general memory and look for the address whose contents
	// are NULL. We return the first address matching the criteria.
	// This works because delete_str garauntees it sets the contents to NULL,
	// before removing the pointer from line_table.
	for (int i = 0; i < total_chunks; i++) {
		if (*(general_buffer[i]) == NULL)
			return general_buffer[i];
	}

	return NULL;
}
