#include <stdexcept>
#include "fib_calc.h"
#include <cctype>

FibonacciCalculator::FibonacciCalculator(ICache &usedCache) : cache(usedCache) {
    hits = 0;
    misses = 0;
}

//метод только для подсчета n-ого числа фибоначи
unsigned long long FibonacciCalculator::computeFibonacci(int n) {
    unsigned long long prev = 0;
    unsigned long long cur = 1;
    if (n == 0) {
        return 0;
    }
    for (int i = 2; i <= n; i++) {
        unsigned long long next = prev + cur;
        prev = cur;
        cur = next;
    }
    return cur;
}

bool FibonacciCalculator::isNumber(const std::string &text) {
    if (text.empty() || text.length() > 2) {
        return false;
    }
    for (std::size_t i = 0; i < text.length(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(text[i]))) {
            return false;
        }
    }
    return true;
}

unsigned long long FibonacciCalculator::calculate(int n, bool &fromCache) {
    if (n < 0 || n > MAX_N) {
        throw std::invalid_argument("n must be from 0 to 93");
    }
    unsigned long long result = 0;
    if (cache.get(n, result)) {
        hits++;
        fromCache = true;
        return result;
    }
    result = computeFibonacci(n);
    cache.put(n, result);
    misses++;
    fromCache = false;
    return result;
}

void FibonacciCalculator::run(std::istream &in, std::ostream &out, std::ostream &err) {
    std::string request;
    while (in >> request) {
        if (request == "exit") {
            break;
        }
        if (request == "stats") {
            out << "hits: " << hits << ", misses: " << misses << ", in cache: " << cache.size() << "/" << cache.capacity() << "\n";
            continue;
        }
        if (!isNumber(request) || std::stoi(request) > MAX_N) {
            err << "wrong request: '" << request << "'. Enter a number from 0 to " << MAX_N << ", 'stats' or 'exit'\n";
            continue;
        }

        int n = std::stoi(request);
        bool fromCache = false;
        unsigned long long result = calculate(n, fromCache);
        out << "fib(" << n << ") = " << result;
        if (fromCache) {
            out << " [cache]\n";
        }
        else {
            out << " [computed]\n";
        }
    }
}

int FibonacciCalculator::getHits() const {
    return hits;
}

int FibonacciCalculator::getMisses() const {
    return misses;
}