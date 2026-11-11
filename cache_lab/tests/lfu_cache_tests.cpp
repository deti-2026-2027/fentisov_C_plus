#include <chrono>
#include <thread>
#include <gtest/gtest.h>
#include "lfu_cache.h"


TEST(LFUCacheConstructor, CreateEmptyCache) {
    LFUCache cache(3);
    EXPECT_EQ(cache.size(), 0u);
}

TEST(LFUCacheConstructor, ZeroCapacity) {
    EXPECT_THROW(LFUCache(0), std::invalid_argument);
}

TEST(LFUCacheConstructor, NegativeTtl) {
    EXPECT_THROW(LFUCache(2, -1), std::invalid_argument);
}


TEST(LFUCacheGet, ReturnStoredValue) {
    LFUCache cache(2);
    cache.put(1, 100);
    unsigned long long value = 0;
    EXPECT_TRUE(cache.get(1, value));
    EXPECT_EQ(value, 100u);
}

TEST(LFUCacheGet,  DeleteByUsing) {
    LFUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    unsigned long long value = 0;
    cache.get(1, value);
    cache.put(3, 30);

    EXPECT_TRUE(cache.get(1, value));
    EXPECT_FALSE(cache.get(2, value));
}

TEST(LFUCacheGet, KeyNotFoundTtl) {
    LFUCache cache(2, 50);
    cache.put(1, 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    unsigned long long value = 0;
    EXPECT_FALSE(cache.get(1, value));
}


TEST(LFUCachePut, AddNewKey) {
    LFUCache cache(2);
    cache.put(1, 10);
    unsigned long long value = 0;
    EXPECT_TRUE(cache.get(1, value));
    EXPECT_EQ(value, 10u);
}

TEST(LFUCachePut, RemoveLeastUsedWhenFul) {
    LFUCache cache(2);
    cache.put(1, 10);
    unsigned long long value = 0;
    cache.get(1, value);
    cache.put(2, 20);
    cache.put(3, 30);

    EXPECT_TRUE(cache.get(1, value));
    EXPECT_FALSE(cache.get(2, value));
    EXPECT_TRUE(cache.get(3, value));
}

TEST(LFUCachePut, SameFrequencyRemoveOldest) {
    LFUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    unsigned long long value = 0;
    EXPECT_FALSE(cache.get(1, value));
    EXPECT_TRUE(cache.get(2, value));
}


TEST(LFUCacheSize, EmptyCacheIsZero) {
    LFUCache cache(2);
    EXPECT_EQ(cache.size(), 0u);
}

TEST(LFUCacheSize, GrowAfterPut) {
    LFUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    EXPECT_EQ(cache.size(), 2u);
}

TEST(LFUCacheSize, LessThanCapacity) {
    LFUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    EXPECT_EQ(cache.size(), 2u);
}


TEST(LFUCacheCapacity, ReturnValueFromConstructor) {
    LFUCache cache(5);
    EXPECT_EQ(cache.capacity(), 5u);
}


TEST(LFUCacheIndexOperator, ReturnValue) {
    LFUCache cache(2);
    cache.put(7, 13);
    EXPECT_EQ(cache[7], 13u);
}

TEST(LFUCacheIndexOperator, ThrowForMissingKey) {
    LFUCache cache(2);
    EXPECT_THROW(cache[7], std::out_of_range);
}