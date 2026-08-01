#pragma once
#include <string>

class IRateLimiter {
public:
    virtual ~IRateLimiter() = default;
    virtual bool allowRequests(const std::string &key) = 0;
};