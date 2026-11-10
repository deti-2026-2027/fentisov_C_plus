#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <chrono>

inline long long currentTimeMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now().time_since_epoch()).count();
}

#endif