#include "services/rate_limiter/sliding_window_counter/swc.hpp"

SlidingWindowCounter::SlidingWindowCounter(std::shared_ptr<ISlidingWindowCounterStorage> storage, SlidingWindowCounterConfig config)
    : storage_(storage), config_(config) {}

bool SlidingWindowCounter::allowRequests(const std::string &key) {
    return this->storage_->try_add(key, config_.window_length, config_.max_requests);
}
