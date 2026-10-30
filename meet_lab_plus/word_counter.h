#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <string>
#include <map>
#include <list>
#include <utility>

class WordCounter {
private:
	std::map<std::string, int> words;
	int totalCount;
	bool isWordChar(char c) const;
	void addWord(const std::string &word);
	static bool compare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);

public:
	WordCounter();
	// разбивает одну строку на слова и учитывает их
	void addLine(const std::string &line);
	int getTotalCount() const;
	bool isEmpty() const;
	std::list<std::pair<std::string, int> > getSortedWords() const;
};

#endif