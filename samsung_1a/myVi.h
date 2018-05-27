// Global Defines.
#define MIN_BLOCK_SIZE 20
#define MAX_TEXT_SIZE 1100
#define MAX_LINES 100

// Function prototypes.
int command_interpreter(char** general_buffer, char* copy_buffer);
int get_blocks(int num_ins);
int insert_str(char** general_buffer, char* text2insert, int* buf_ptr, int position);
int delete_str(char** general_buffer, int* buf_ptr, int* position, int* cur_buf_size, char** line_table);
int copy_str(char** general_buffer, char* copy_buffer, int buf_ptr, int* valid_paste);
int paste_str(char** general_buffer, char* copy_buffer, int buf_ptr, int* position, int* valid_paste);
int move_cur(char** general_buffer, int* buf_ptr, int* position);
int print(char**, int*);
int update_table(char** line_table, int deleted_line, int);
char* findMemory(char** line_table, char** general_buffer, int total_chunks);