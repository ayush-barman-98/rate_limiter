#include "fws.hpp"

FixedWindowCounter::FixedWindowCounter(std::shared_ptr<IFixedWindowCounterStorage> storage, FixedWindowCounterConfig config)
    : storage_(storage), config_(config) {}

bool FixedWindowCounter::allowRequests(const std::string &key) {
    const int64_t current_window_request_count = storage_->increment(key, config_.window_length_seconds);
    return current_window_request_count <= config_.max_requests;
}

