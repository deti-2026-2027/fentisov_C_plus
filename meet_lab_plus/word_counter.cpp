#include <cctype>
#include "word_counter.h"

WordCounter::WordCounter() {
	totalCount = 0;
}

bool WordCounter::isWordChar(char c) const {
	return std::isalpha((unsigned char)c) != 0;
}

void WordCounter::addWord(const std::string &word) {
	words[word]++;
	totalCount++;
}

bool WordCounter::compare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
	if (a.second != b.second) {
		return a.second > b.second;
	}
	return a.first < b.first;
}

void WordCounter::addLine(const std::string &line) {
	std::string word;
	for (size_t i = 0; i < line.length(); i++) {
		if (isWordChar(line[i])) {
			word += line[i];
		} else if (!word.empty()) {
			addWord(word);
			word.clear();
		}
	}
	if (!word.empty()) {
		addWord(word);
	}
}

int WordCounter::getTotalCount() const {
	return totalCount;
}

bool WordCounter::isEmpty() const {
	return words.empty();
}

std::list<std::pair<std::string, int> > WordCounter::getSortedWords() const {
	std::list<std::pair<std::string, int> > result(words.begin(), words.end());
	result.sort(compare);
	return result;
}