#include <stdio.h>
#include "file_io.h"
#include "structures.h"
#include "utils.h"
#include "errors.h"



int main(int argc, char *argv[]) {
	if (argc < 3) {
		print_help();
		return error_args;
	}
	char *input_file = argv[1];
	char *output_file = argv[2];
	char *buffer = NULL;
	size_t buffer_size = 0;
	error_code err = read_file(input_file, &buffer, &buffer_size);
	if (err != success) {
		print_error(err);
		return err;
	}
	WordList list;
	err = count_words(buffer, &list);
	if (err != success) {
		print_error(err);
		free(buffer);
		return err;
	}
	sort_by_freq(&list);
	err = write_csv(output_file, &list);
	if (err != success) {
		print_error(err);
		free_word_list(&list);
		free(buffer);
		return err;
	}
	free_word_list(&list);
	free(buffer);
	return success;
}
