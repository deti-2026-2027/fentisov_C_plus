#ifndef FIBONACCI_CALCULATOR_H
#define FIBONACCI_CALCULATOR_H

#include <istream>
#include <ostream>
#include <string>
#include "Icache.h"

class FibonacciCalculator {
private:
	ICache &cache;
	int hits;      // сколько ответов взяли из кэша
	int misses;    // сколько ответов пришлось считать

	static unsigned long long computeFibonacci(int n);
	static bool isNumber(const std::string &text);

public:
	static const int MAX_N = 93;

	FibonacciCalculator(ICache &usedCache);
	
	unsigned long long calculate(int n, bool &fromCache);

	// консольный режим, запросы: число n, "stats" или "exit"
	void run(std::istream &in, std::ostream &out, std::ostream &err);
	int getHits() const;
	int getMisses() const;
};

#endif