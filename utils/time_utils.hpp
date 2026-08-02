#pragma once

#include <chrono>
#include <cstdint>

namespace utils {

/**
 * Returns the current epoch timestamp in seconds.
 */
inline int64_t getCurrentTimeInSeconds() {
    return std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

/**
 * Returns the current epoch timestamp in milliseconds.
 */
inline int64_t getCurrentTimeInMilliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

} // namespace utils
