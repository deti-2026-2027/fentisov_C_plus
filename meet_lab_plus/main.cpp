#include <iostream>
#include <string>
#include <list>
#include "errors.h"
#include "structures.h"
#include "file_io.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		Errors::printHelp();
		return error_args;
	}

	std::string inputFile = argv[1];
	std::string outputFile = argv[2];

	FileIO fileIO;
	WordCounter counter;

	// читаем файл
	std::list<std::string> lines;
	ErrorCode err = fileIO.readFile(inputFile, lines);
	if (err != success) {
		Errors::printError(err);
		return err;
	}

	// считаем слова
	WordList wordList;
	err = counter.countWords(lines, wordList);
	if (err != success) {
		Errors::printError(err);
		return err;
	}

	// сортируем по частоте
	std::list<std::pair<std::string, int> > sortedWords = counter.sortByFreq(wordList);

	// записываем в csv
	err = fileIO.writeCsv(outputFile, sortedWords, wordList.getTotalCount());
	if (err != success) {
		Errors::printError(err);
		return err;
	}
	return success;
}