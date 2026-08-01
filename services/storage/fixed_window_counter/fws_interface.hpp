#pragma once
#include <string>
#include <cstdint>

class IFixedWindowCounterStorage {
public:
    virtual ~IFixedWindowCounterStorage() = default;
    virtual int64_t increment(const std::string &key, int window_size) = 0;
    virtual int64_t get(const std::string &key) = 0;
    virtual void remove(const std::string &key) = 0;
};