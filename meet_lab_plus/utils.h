#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <list>
#include <utility>
#include "structures.h"
#include "errors.h"

// класс, который считает слова и сортирует результат
class WordCounter {
private:
	bool isWordChar(char c) const;

	// сравнение по величине частоты, в случае равенства - по алфавиту
	static bool compare(const std::pair<std::string, int> &a,
						const std::pair<std::string, int> &b);

public:
	// разбивает строки на слова и заполняет WordList
	ErrorCode countWords(const std::list<std::string> &lines, WordList &wordList);

	// возвращает слова, отсортированные по убыванию частоты
	std::list<std::pair<std::string, int> > sortByFreq(const WordList &wordList);
};

#endif