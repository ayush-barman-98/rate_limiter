#pragma once
#include "../rate_limiter.hpp"
#include "../../storage/fixed_window_counter/fws_interface.hpp"
#include <memory>

struct FixedWindowCounterConfig {
    int64_t max_requests;
    int64_t window_length_seconds;
};

class FixedWindowCounter : public IRateLimiter {
private:
    std::shared_ptr<IFixedWindowCounterStorage> storage_;
    FixedWindowCounterConfig config_;

public:
    FixedWindowCounter(std::shared_ptr<IFixedWindowCounterStorage> storage, FixedWindowCounterConfig config);
    
    bool allowRequests(const std::string &key) override;
};