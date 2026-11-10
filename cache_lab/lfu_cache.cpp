#include "lfu_cache.h"
#include "time_utils.h"

LFUCache::LFUCache(std::size_t cacheCapacity, long long ttl) {
    if (cacheCapacity == 0) {
        throw std::invalid_argument("capacity must be greater than 0");
    }
    if (ttl < 0) {
        throw std::invalid_argument("ttl must not be negative");
    }
    maxSize = cacheCapacity;
    ttlMs = ttl;
    useCount = 0;
}

bool LFUCache::isExpired(const Entry &entry) const {
    if (ttlMs == 0) {
        return false;
    }
    return currentTimeMs() - entry.added_time >= ttlMs;
}

void LFUCache::markUsed(Entry &entry) {
    entry.frequency++;
    useCount++;
    entry.lastUse = useCount;
}

int LFUCache::findKeyToRemove() const {
    int keyToRemove = 0;
    int minFrequency = 0;
    long long oldestUse = 0;
    bool first = true;

    for (const std::pair<const int, Entry> &item : items) {
        const Entry &entry = item.second;
        bool rarer = entry.frequency < minFrequency;
        bool last_of_used = entry.frequency == minFrequency && entry.lastUse < oldestUse;
        if (first || rarer || last_of_used) {
            keyToRemove = item.first;
            minFrequency = entry.frequency;
            oldestUse = entry.lastUse;
            first = false;
        }
    }
    return keyToRemove;
}

bool LFUCache::get(int key, unsigned long long &value) {
    if (items.count(key) == 0) {
        return false;
    }
    if (isExpired(items[key])) {
        items.erase(key);
        return false;
    }
    markUsed(items[key]);
    value = items[key].value;
    return true;
}

void LFUCache::put(int key, unsigned long long value) {
    if (items.count(key) != 0) {
        items[key].added_time = currentTimeMs();
        markUsed(items[key]);
        return;
    }

    if (items.size() == maxSize) {
        items.erase(findKeyToRemove());
    }

    Entry entry;
    entry.value = value;
    entry.frequency = 0;
    entry.added_time = currentTimeMs();
    markUsed(entry);
    items[key] = entry;
}

std::size_t LFUCache::size() const {
    return items.size();
}

std::size_t LFUCache::capacity() const {
    return maxSize;
}