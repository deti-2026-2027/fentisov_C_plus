#ifndef LAB0_STRUCTURES_H
#define LAB0_STRUCTURES_H

typedef struct {
	char* word;
	int count;
} Word;

typedef struct {
	Word* words;
	size_t length;
	int total_count;
} WordList;

#endif
