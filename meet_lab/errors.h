#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
	success = 0,
	error_file_not_found = 1,
	error_read = 2,
	error_write = 3,
	error_empty_input = 4,
	error_args = 5,
	error_memory = 6
} error_code;

void print_help();

void print_error(error_code code);

#endif