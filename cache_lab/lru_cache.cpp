#include "lru_cache.h"
#include "time_utils.h"

LRUCache::LRUCache(std::size_t cacheCapacity, long long ttl) {
	if (cacheCapacity == 0) {
		throw std::invalid_argument("capacity must be greater than 0");
	}
	if (ttl < 0) {
		throw std::invalid_argument("ttl mustn't be negative");
	}
	maxSize = cacheCapacity;
	ttlMs = ttl;
}

bool LRUCache::isExpired(const Entry &entry) const {
	if (ttlMs == 0) {
		return false;
	}
	return (currentTimeMs() - entry.added_time) >= ttlMs;
}

void LRUCache::moveToFront(int key) {
	order.remove(key);
	order.push_front(key);
}

void LRUCache::remove(int key) {
	order.remove(key);
	items.erase(key);
}

bool LRUCache::get(int key, unsigned long long &value) {
	if (items.count(key) == 0) {
		return false;
	}
	if (isExpired(items[key])) {
		remove(key);
		return false;
	}
	moveToFront(key);
	value = items[key].value;
	return true;
}

void LRUCache::put(int key, unsigned long long value) {
	if (items.count(key) != 0) {
		items[key].added_time = currentTimeMs();
		moveToFront(key);
		return;
	}

	if (items.size() == maxSize) {
		remove(order.back());
	}

	Entry entry;
	entry.value = value;
	entry.added_time = currentTimeMs();
	items[key] = entry;
	order.push_front(key);
}

std::size_t LRUCache::size() const {
	return items.size();
}

std::size_t LRUCache::capacity() const {
	return maxSize;
}