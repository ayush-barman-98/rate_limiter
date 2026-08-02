#include "services/rate_limiter/sliding_window_log/swl.hpp"

SlidingWindowLog::SlidingWindowLog(std::shared_ptr<ISlidingWindowLogStorage> storage, SlidingWindowLogConfig config)
    : storage_(storage), config_(config) {}

bool SlidingWindowLog::allowRequests(const std::string &key) {
    return storage_->try_add(key, config_.window_length, config_.max_requests);
}