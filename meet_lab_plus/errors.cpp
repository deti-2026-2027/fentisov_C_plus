#include <iostream>
#include "errors.h"

void Errors::printHelp() {
	std::cout << "Usage: word_count.exe input.txt output.csv" << std::endl;
	std::cout << "Description of app:" << std::endl;
	std::cout << "  Counts word frequencies in input file" << std::endl;
	std::cout << "  and writes a CSV to output file with columns:" << std::endl;
	std::cout << "  Word, Frequency, Frequency %. Sorting by descending frequency" << std::endl;
}

void Errors::printError(ErrorCode code) {
	if (code == error_file_not_found) {
		std::cout << "File not found" << std::endl;
	}
	else if (code == error_read) {
		std::cout << "Read error" << std::endl;
	}
	else if (code == error_write) {
		std::cout << "Write error" << std::endl;
	}
	else if (code == error_empty_input) {
		std::cout << "Empty input" << std::endl;
	}
	else if (code == error_args) {
		std::cout << "Argument error" << std::endl;
	}
}
