#include "utils.h"

#include <ctype.h>

#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
	const Word *word_a = (const Word *) a;
	const Word *word_b = (const Word *) b;
	if (word_b->count != word_a->count) {
		return word_b->count - word_a->count;
	}
	return strcmp(word_b->word, word_a->word);
}

int compare_words(const void *a, const void *b) {
	const char *const *sa = (const char *const *) a;
	const char *const *sb = (const char *const *) b;
	return strcmp(*sa, *sb);
}

void sort_by_freq(WordList *list) {
	qsort(list->words, list->length, sizeof(Word), compare);
}


error_code get_words(char* buffer, char ***out, size_t *out_length) {
	size_t count = 0;
	size_t capacity = 1024;
	char **result = (char **) malloc(capacity * sizeof(char *));
	if (result == NULL) {
		return error_memory;
	}
	char *p = buffer;
	while (*p != '\0') {
		while (*p != '\0' && !isalnum(*p) && !isdigit(*p)) {
			p++;
		}
		if (*p == '\0') {
			break;
		}
		char *start = p;
		while (*p != '\0' && (isalnum(*p) || isdigit(*p))) {
			p++;
		}
		size_t word_len = p - start;
		char *word = (char *) malloc((word_len + 1) * sizeof(char));
		if (word == NULL) {
			for (size_t i = 0; i < count; i++) {
				free(result[i]);
			}
			free(result);
			return error_memory;
		}
		for (size_t i = 0; i <= word_len; i++) {
			word[i] = start[i];
		}
		word[word_len] = '\0';
		if (count == capacity) {
			capacity <<= 1;
			result = (char **) realloc(result, capacity * sizeof(char *));
			if (result == NULL) {
				for (size_t i = 0; i < count; i++) {
					free(result[i]);
				}
				free(result);
				return error_memory;
			}
		}
		result[count++] = word;

	}
	*out = result;
	*out_length = count;
	return success;
}

error_code count_words(char* buffer, WordList *list) {
	if (buffer == NULL || list == NULL) {
		return error_args;
	}
	char **words = NULL;
	size_t words_len = 0;
	error_code result = get_words(buffer, &words, &words_len);
	if (result != success) {
		return result;
	}
	int unique = 0;
	qsort(words, words_len, sizeof(char *), compare_words);
	for (size_t i = 1; i < words_len; i++) {
		if (strcmp(words[i - 1], words[i]) != 0) {
			unique++;
		}
	}
	Word *data = (Word *) malloc(sizeof(Word) * unique);
	if (data == NULL) {
		for (size_t i = 0; i < words_len; i++) {
			free(words[i]);
		}
		free(words);
		return error_memory;
	}
	size_t i = 0;
	size_t result_index = 0;
	while (i < words_len) {
		size_t j = i;
		while (j < words_len && strcmp(words[i], words[j]) == 0) {
			j++;
		}
		data[result_index].word = words[i];
		data[result_index].count = j - i;
		result_index++;
		for (size_t k = i + 1; k < j; k++) {
			free(words[k]);
		}
		i = j;
	}
	free(words);
	list->words = data;
	list->length = result_index;
	list->total_count = (int)words_len;
	return success;
}

void free_word_list(WordList *list) {
	if (list == NULL) {
		return;
	}
	for (size_t i = 0; i < list->length; i++) {
		free(list->words[i].word);
	}
	free(list->words);
}