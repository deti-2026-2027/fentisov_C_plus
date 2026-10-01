#include <stdio.h>
#include "errors.h"

void print_help() {
	printf("Usage: word_count.exe input.txt output.csv\n");
	printf("Description:\n");
	printf("  Counts word frequencies in INPUT_FILE (words = combination of letters/digits)\n");
	printf("  and writes a CSV to OUTPUT_FILE with columns:\n");
	printf("  Word, Frequency, Frequency %%. Sorting by descending frequency\n");
}

void print_error(error_code code) {
	if (code == error_file_not_found) {
		printf("File not found\n");
	}
	else if (code == error_read) {
		printf("Read error\n");
	}
	else if (code == error_write) {
		printf("Write error\n");
	}
	else if (code == error_empty_input) {
		printf("Empty input\n");
	}
	else if (code == error_args) {
		printf("Argument error\n");
	}
}