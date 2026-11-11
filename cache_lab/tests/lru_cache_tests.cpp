#include <chrono>
#include <thread>
#include <gtest/gtest.h>
#include "lru_cache.h"


TEST(LRUCacheConstructor, CreateEmptyCache) {
	LRUCache cache(3);
	EXPECT_EQ(cache.size(), 0u);
}

TEST(LRUCacheConstructor, ZeroCapacity) {
	EXPECT_THROW(LRUCache(0), std::invalid_argument);
}

TEST(LRUCacheConstructor, NegativeTtl) {
	EXPECT_THROW(LRUCache(2, -1), std::invalid_argument);
}


TEST(LRUCacheGet, ReturnStoredValue) {
	LRUCache cache(2);
	cache.put(1, 100);
	unsigned long long value = 0;
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_EQ(value, 100u);
}

TEST(LRUCacheGet, DeleteByRecent) {
	LRUCache cache(2);
	cache.put(1, 10);
	cache.put(2, 20);
	unsigned long long value = 0;
	cache.get(1, value);
	cache.put(3, 30);

	EXPECT_TRUE(cache.get(1, value));
	EXPECT_FALSE(cache.get(2, value));
}

TEST(LRUCacheGet, KeyNotFoundTtl) {
	LRUCache cache(2, 50);
	cache.put(1, 10);
	std::this_thread::sleep_for(std::chrono::milliseconds(80));
	unsigned long long value = 0;
	EXPECT_FALSE(cache.get(1, value));
}


TEST(LRUCachePut, AddNewKey) {
	LRUCache cache(2);
	cache.put(1, 10);
	unsigned long long value = 0;
	EXPECT_TRUE(cache.get(1, value));
	EXPECT_EQ(value, 10u);
}

TEST(LRUCachePut, RemoveOldestWhenFull) {
	LRUCache cache(2);
	cache.put(1, 10);
	cache.put(2, 20);
	cache.put(3, 30);

	unsigned long long value = 0;
	EXPECT_FALSE(cache.get(1, value));
	EXPECT_TRUE(cache.get(2, value));
	EXPECT_TRUE(cache.get(3, value));
}

TEST(LRUCachePut, DuplicateSameKeys) {
	LRUCache cache(2);
	cache.put(1, 10);
	cache.put(1, 10);
	EXPECT_EQ(cache.size(), 1u);
}


TEST(LRUCacheSize, EmptyCacheIsZero) {
	LRUCache cache(2);
	EXPECT_EQ(cache.size(), 0u);
}

TEST(LRUCacheSize, GrowAfterPut) {
	LRUCache cache(3);
	cache.put(1, 10);
	cache.put(2, 20);
	EXPECT_EQ(cache.size(), 2u);
}

TEST(LRUCacheSize, LessThanCapacity) {
	LRUCache cache(2);
	cache.put(1, 10);
	cache.put(2, 20);
	cache.put(3, 30);
	EXPECT_EQ(cache.size(), 2u);
}


TEST(LRUCacheCapacity, ReturnValueFromConstructor) {
	LRUCache cache(5);
	EXPECT_EQ(cache.capacity(), 5u);
}


TEST(LRUCacheIndexOperator, ReturnValue) {
	LRUCache cache(2);
	cache.put(7, 13);
	EXPECT_EQ(cache[7], 13u);
}

TEST(LRUCacheIndexOperator, ThrowForMissingKey) {
	LRUCache cache(2);
	EXPECT_THROW(cache[7], std::out_of_range);
}
