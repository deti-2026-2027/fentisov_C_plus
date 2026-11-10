#include <iostream>
#include <string>
#include <stdexcept>
#include "I	cache.h"
#include "lru_cache.h"
#include "lfu_cache.h"
#include "fib_calc.h"

static void printHelp() {
	std::cerr << "Usage: cache_app <lru|lfu> <capacity> [ttl_ms]" << std::endl;
	std::cerr << "  lru|lfu  - cache type" << std::endl;
	std::cerr << "  capacity - how many values the cache keeps (> 0)" << std::endl;
	std::cerr << "  ttl_ms   - optional: how long a value lives, in ms (0 = forever)" << std::endl;
}

// принимает любой кэш по ссылке на интерфейс и запускает консольный режим
static void runCalculator(ICache &cache) {
	FibonacciCalculator calculator(cache);
	std::cout << "Enter n to get fib(n) (0.." << FibonacciCalculator::MAX_N << "), 'stats' or 'exit'" << std::endl;
	calculator.run(std::cin, std::cout, std::cerr);
}

int main(int argc, char *argv[]) {
	if (argc < 3 || argc > 4) {
		printHelp();
		return 1;
	}
	std::string type = argv[1];
	long long capacity = 0;
	long long ttl = 0;
	try {
		capacity = std::stoll(argv[2]);
		if (argc == 4) {
			ttl = std::stoll(argv[3]);
		}
	}
	catch (const std::exception &) {
		std::cerr << "capacity and ttl_ms must be numbers" << std::endl;
		return 1;
	}
	if (capacity <= 0 || ttl < 0) {
		std::cerr << "capacity must be > 0 and ttl_ms must be >= 0" << std::endl;
		return 1;
	}
	if (type == "lru") {
		LRUCache cache(capacity, ttl);
		runCalculator(cache);
	}
	else if (type == "lfu") {
		LFUCache cache(capacity, ttl);
		runCalculator(cache);
	}
	else {
		std::cerr << "Unknown cache type: " << type << std::endl;
		printHelp();
		return 1;
	}
	return 0;
}