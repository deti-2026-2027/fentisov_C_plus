#ifndef ICACHE_H
#define ICACHE_H

#include <cstddef>
#include <stdexcept>

class ICache {
public:
	virtual ~ICache() {}

	virtual bool get(int key, unsigned long long &value) = 0;

	virtual void put(int key, unsigned long long value) = 0;

	virtual std::size_t size() const = 0;

	virtual std::size_t capacity() const = 0;

	unsigned long long operator[](int key) {
		unsigned long long value = 0;
		if (!get(key, value)) {
			throw std::out_of_range("key is not in cache");
		}
		return value;
	}
};

#endif