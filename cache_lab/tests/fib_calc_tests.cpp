#include <sstream>
#include <gtest/gtest.h>
#include "fib_calc.h"
#include "lru_cache.h"


TEST(FibonacciCalculatorCalculate, ReturnCorrectValues) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    bool fromCache = false;

    EXPECT_EQ(calculator.calculate(0, fromCache), 0u);
    EXPECT_EQ(calculator.calculate(1, fromCache), 1u);
    EXPECT_EQ(calculator.calculate(10, fromCache), 55u);
    EXPECT_EQ(calculator.calculate(93, fromCache), 12200160415121876738ull);
}

TEST(FibonacciCalculatorCalculate, OutOfRangeThrows) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    bool fromCache = false;

    EXPECT_THROW(calculator.calculate(-1, fromCache), std::invalid_argument);
    EXPECT_THROW(calculator.calculate(94, fromCache), std::invalid_argument);
}

TEST(FibonacciCalculatorCalculate, SecondRequestComesFromCache) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    bool fromCache = true;

    calculator.calculate(10, fromCache);
    EXPECT_FALSE(fromCache);
    EXPECT_EQ(calculator.calculate(10, fromCache), 55u);
    EXPECT_TRUE(fromCache);
}


TEST(FibonacciCalculatorGetHits, HitsStartWithZero) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    EXPECT_EQ(calculator.getHits(), 0);
}

TEST(FibonacciCalculatorGetHits, CountsAnswersFromCache) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    bool fromCache = false;

    calculator.calculate(10, fromCache);
    calculator.calculate(10, fromCache);
    calculator.calculate(10, fromCache);
    EXPECT_EQ(calculator.getHits(), 2);
}


TEST(FibonacciCalculatorGetMisses, MissesStartWithZero) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    EXPECT_EQ(calculator.getMisses(), 0);
}

TEST(FibonacciCalculatorGetMisses, CountsComputedAnswers) {
    LRUCache cache(10);
    FibonacciCalculator calculator(cache);
    bool fromCache = false;

    calculator.calculate(10, fromCache);
    calculator.calculate(11, fromCache);
    calculator.calculate(10, fromCache);
    EXPECT_EQ(calculator.getMisses(), 2);
}


TEST(FibonacciCalculatorRun, AnswersRequests) {
    LRUCache cache(5);
    FibonacciCalculator calculator(cache);
    std::istringstream in("10 10\n");
    std::ostringstream out;
    std::ostringstream err;
    calculator.run(in, out, err);
    EXPECT_EQ(out.str(),
              "fib(10) = 55 [computed]\n"
              "fib(10) = 55 [cache]\n");
}

TEST(FibonacciCalculatorRun, ExitStopsProcessing) {
    LRUCache cache(5);
    FibonacciCalculator calculator(cache);
    std::istringstream in("exit\n10\n");
    std::ostringstream out;
    std::ostringstream err;

    calculator.run(in, out, err);
    EXPECT_EQ(out.str(), "");
}

TEST(FibonacciCalculatorRun, ErrorStream) {
    LRUCache cache(5);
    FibonacciCalculator calculator(cache);
    std::istringstream in("abc 94\n");
    std::ostringstream out;
    std::ostringstream err;

    calculator.run(in, out, err);
    EXPECT_EQ(out.str(), "");
    EXPECT_NE(err.str().find("'abc'"), std::string::npos);
    EXPECT_NE(err.str().find("'94'"), std::string::npos);
}