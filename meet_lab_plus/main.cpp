#include <iostream>
#include <string>
#include <list>
#include "errors.h"
#include "file_io.h"
#include "word_counter.h"

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
	ErrorCode err = fileIO.readFile(inputFile, counter);
	if (err != success) {
		Errors::printError(err);
		return err;
	}
	//получаем список отсортированных слов
	std::list<std::pair<std::string, int> > sortedWords = counter.getSortedWords();

	// записываем в csv
	err = fileIO.writeCsv(outputFile, sortedWords, counter.getTotalCount());
	if (err != success) {
		Errors::printError(err);
		return err;
	}
	return success;
}