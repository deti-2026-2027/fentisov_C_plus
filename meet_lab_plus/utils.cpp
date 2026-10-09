#include "utils.h"

bool WordCounter::isWordChar(char c) const {
	return std::isalpha((unsigned char)c) != 0;
}

bool WordCounter::compare(const std::pair<std::string, int> &a,
						  const std::pair<std::string, int> &b) {
	if (a.second != b.second) {
		return a.second > b.second;
	}
	return a.first < b.first;
}

ErrorCode WordCounter::countWords(const std::list<std::string> &lines, WordList &wordList) {
	for (const std::string &line : lines) {
		std::string word;
		for (size_t i = 0; i < line.length(); i++) {
			if (isWordChar(line[i])) {
				word += line[i];
			} else if (!word.empty()) {
				wordList.addWord(word);
				word.clear();
			}
		}
		if (!word.empty()) {
			wordList.addWord(word);
		}
	}

	if (wordList.isEmpty()) {
		return error_empty_input;
	}
	return success;
}

std::list<std::pair<std::string, int> > WordCounter::sortByFreq(const WordList &wordList) {
	// Копируем пары из map в list и сортируем
	std::list<std::pair<std::string, int> > result(wordList.getWords().begin(),wordList.getWords().end());
	result.sort(compare);
	return result;
}