#include <fstream>
#include "file_io.h"


ErrorCode FileIO::readFile(const std::string &fileName, WordCounter &counter) {
	std::ifstream input_file(fileName.c_str());
	if (!input_file.is_open()) {
		return error_file_not_found;
	}
	std::string line;
	while (std::getline(input_file, line)) {
		counter.addLine(line);
	}

	if (!input_file.eof()) {
		input_file.close();
		return error_read;
	}
	input_file.close();

	if (counter.isEmpty()) {
		return error_empty_input;
	}
	return success;
}

ErrorCode FileIO::writeCsv(const std::string &fileName,
						   const std::list<std::pair<std::string, int> > &sortedWords,
						   int totalCount) {
	std::ofstream fout(fileName.c_str());
	if (!fout.is_open()) {
		return error_write;
	}
	fout << "Word,Frequency,Frequency %" << std::endl;
	for (std::pair<std::string, int> p : sortedWords) {
		double percent = p.second * 100.0 / totalCount;
		fout << p.first << "," << p.second << "," << percent << std::endl;
	}

	if (fout.fail()) {
		fout.close();
		return error_write;
	}
	fout.close();
	return success;
}