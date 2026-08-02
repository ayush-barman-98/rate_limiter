#pragma once
#include <string>
#include <cstdint>

class ISlidingWindowLogStorage {  
public:    
    virtual ~ISlidingWindowLogStorage() = default;
    virtual bool try_add(const std::string &key, int64_t window_size, int64_t capacity) = 0;
    virtual int64_t get_count(const std::string &key) = 0;
    virtual void remove(const std::string &key) = 0;
};