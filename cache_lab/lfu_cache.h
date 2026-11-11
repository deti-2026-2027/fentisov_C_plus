#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <map>
#include "Icache.h"

class LFUCache : public ICache {
private:
	struct Entry {
		unsigned long long value;
		int frequency;
		long long lastUse;
		long long added_time;
	};

	std::size_t maxSize;
	long long ttlMs;
	long long useCount;
	std::map<int, Entry> items;

	bool isExpired(const Entry &entry) const;
	void markUsed(Entry &entry);
	int findKeyToRemove() const;

public:
	LFUCache(std::size_t cacheCapacity, long long ttl = 0);

	bool get(int key, unsigned long long &value) override;
	void put(int key, unsigned long long value) override;
	std::size_t size() const override;
	std::size_t capacity() const override;
};

#endif