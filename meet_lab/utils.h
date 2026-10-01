#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include "structures.h"
#include "errors.h"

int compare(const void *a, const void *b);

int compare_words(const void *a, const void *b);

void sort_by_freq(WordList *list);

error_code get_words(char* buffer, char ***out, size_t *out_length);

error_code count_words(char* buffer, WordList *list);

void free_word_list(WordList *list);

#endif
