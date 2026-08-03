#pragma once

#include "services/rate_limiter/rate_limiter.hpp"
#include "services/storage/sliding_window_counter/swc_interface.hpp"
#include <memory>
#include <string>
#include <cstdint>

struct SlidingWindowCounterConfig {
    int64_t max_requests;
    int64_t window_length;
};

class SlidingWindowCounter : public IRateLimiter {
private:
    std::shared_ptr<ISlidingWindowCounterStorage> storage_;
    SlidingWindowCounterConfig config_;

public:
    SlidingWindowCounter(std::shared_ptr<ISlidingWindowCounterStorage> storage, SlidingWindowCounterConfig config);

    bool allowRequests(const std::string &key) override;
};
