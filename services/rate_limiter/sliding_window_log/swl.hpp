#pragma once

#include "services/rate_limiter/rate_limiter.hpp"
#include "services/storage/sliding_window_log/swl_interface.hpp"
#include <memory>
#include <string>
#include <cstdint>

struct SlidingWindowLogConfig {
    int64_t max_requests;
    int64_t window_length;
};

class SlidingWindowLog : public IRateLimiter {
private:
    std::shared_ptr<ISlidingWindowLogStorage> storage_;
    SlidingWindowLogConfig config_;

public:
    SlidingWindowLog(std::shared_ptr<ISlidingWindowLogStorage> storage, SlidingWindowLogConfig config);

    bool allowRequests(const std::string &key) override;
};
