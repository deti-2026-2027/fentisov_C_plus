#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <map>

// класс, который хранит слова и сколько раз каждое встретилось
class WordList {
private:
	std::map<std::string, int> words; // слово и его частота
	int totalCount;                   // всего слов в тексте

public:
	WordList() {
		totalCount = 0;
	}

	void addWord(const std::string &word) {
		words[word]++;
		totalCount++;
	}

	int getTotalCount() const {
		return totalCount;
	}

	bool isEmpty() const {
		return words.empty();
	}

	const std::map<std::string, int> &getWords() const {
		return words;
	}
};

#endif