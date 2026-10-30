#ifndef ERRORS_H
#define ERRORS_H

enum ErrorCode {
	success = 0,
	error_file_not_found = 1,
	error_read = 2,
	error_write = 3,
	error_empty_input = 4,
	error_args = 5
};

// класс для вывода сообщений об ошибках
class Errors {
public:
	static void printHelp();
	static void printError(ErrorCode code);
};

#endif