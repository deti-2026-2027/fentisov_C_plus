#ifndef FILE_IO_H
#define FILE_IO_H
#include "errors.h"
#include "structures.h"

char* get_filename(char* path);

error_code read_file(char *file_name, char **buffer, size_t *buffer_size);

error_code write_csv(char *file_name, WordList *list);

#endif
