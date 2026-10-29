#include <iostream>
#include "errors.h"

void Errors::printHelp() {
	std::cerr << "Usage: word_count.exe input.txt output.csv" << std::endl;
	std::cerr << "Description of app:" << std::endl;
	std::cerr << "  Counts word frequencies in input file" << std::endl;
	std::cerr << "  and writes a CSV to output file with columns:" << std::endl;
	std::cerr << "  Word, Frequency, Frequency %. Sorting by descending frequency" << std::endl;
}

void Errors::printError(ErrorCode code) {
	if (code == error_file_not_found) {
		std::cerr << "File not found" << std::endl;
	}
	else if (code == error_read) {
		std::cerr << "Read error" << std::endl;
	}
	else if (code == error_write) {
		std::cerr << "Write error" << std::endl;
	}
	else if (code == error_empty_input) {
		std::cerr << "Empty input" << std::endl;
	}
	else if (code == error_args) {
		std::cerr << "Argument error" << std::endl;
	}
}
