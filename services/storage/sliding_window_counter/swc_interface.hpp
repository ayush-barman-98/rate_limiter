#pragma once

#include <string>
#include <cstdint>

class ISlidingWindowCounterStorage {
public:
    virtual ~ISlidingWindowCounterStorage() = default;
    virtual bool try_add(const std::string &key, int64_t window_size, int64_t capacity) = 0;
    virtual double get_estimated_count(const std::string &key, int64_t window_size) = 0;
    virtual void remove(const std::string &key) = 0;
};