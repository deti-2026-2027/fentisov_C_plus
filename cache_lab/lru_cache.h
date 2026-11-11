#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <map>
#include "Icache.h"

class LRUCache : public ICache {
private:
	struct Entry {
		unsigned long long value;
		long long added_time;
	};

	std::size_t maxSize;
	long long ttlMs;
	std::list<int> order;
	std::map<int, Entry> items;

	bool isExpired(const Entry &entry) const;
	void moveToFront(int key); 
	void remove(int key);

public:
	LRUCache(std::size_t cacheCapacity, long long ttl = 0);

	bool get(int key, unsigned long long &value) override;
	void put(int key, unsigned long long value) override;
	std::size_t size() const override;
	std::size_t capacity() const override;
};

#endif