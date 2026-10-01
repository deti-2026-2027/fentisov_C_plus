#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "file_io.h"
#include "structures.h"

char* get_filename(char* path) {
	char* p1 = strrchr(path, '/');
	char* p2 = strrchr(path, '\\');
	char* p = (p1 > p2) ? p1 : p2;
	return p ? p + 1 : path;
}

error_code read_file(char *file_name, char **buffer, size_t *buffer_size) {
	if (file_name == NULL || buffer == NULL || buffer_size == NULL) {
		return error_args;
	}
	FILE *file = fopen(file_name, "rb");
	if (file == NULL) {
		return error_file_not_found;
	}
	if (fseek(file, 0, SEEK_END) != 0) {
		fclose(file);
		return error_read;
	}
	long file_size = ftell(file);
	if (file_size == 0) {
		fclose(file);
		return error_empty_input;
	}
	if (file_size < 0) {
		fclose(file);
		return error_read;
	}
	if (fseek(file, 0, SEEK_SET) != 0) {
		fclose(file);
		return error_read;
	}
	char *data = (char*)malloc((size_t)file_size + 1);
	if (data == NULL) {
		fclose(file);
		return error_memory;
	}
	size_t bytes = fread(data, 1, (size_t)file_size, file);
	data[bytes] = '\0';
	*buffer = data;
	*buffer_size = bytes;
	fclose(file);
	return success;
}

error_code write_csv(char *file_name, WordList *list) {
	if (file_name == NULL || list == NULL) {
		return error_args;
	}
	FILE *file = fopen(file_name, "wb");
	if (file == NULL) {
		return error_file_not_found;
	}
	if (fprintf(file, "Word, frequency, frequency(%%)\n") <0) {
		fclose(file);
		return error_write;
	}
	for (int i = 0; i < list->length; i++) {
		double frequency = ((double)list->words[i].count * 100.0) / ((double)list->total_count) ;
		if (fprintf(file, "%s %d %.2f\n" , list->words[i].word, list->words[i].count, frequency) < 0) {
			fclose(file);
			return error_write;
		}
	}
	fclose(file);
	return success;
}

