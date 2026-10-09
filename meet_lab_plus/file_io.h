#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <list>
#include <utility>
#include "errors.h"

// класс для работы с файлами
class FileIO {
public:
	// читает файл построчно и складывает строки в list
	ErrorCode readFile(const std::string &fileName, std::list<std::string> &lines);

	// записывает csv, где sortedWords уже отсортирован по убыванию
	ErrorCode writeCsv(const std::string &fileName, const std::list<std::pair<std::string, int>> &sortedWords, int totalCount);
};

#endif