#pragma once
#include "services/storage/sliding_window_log/swl_interface.hpp"
#include <unordered_map>
#include <deque>
#include <mutex>
#include <string>
#include <cstdint>

class InMemorySlidingWindowLogStorage : public ISlidingWindowLogStorage {
private:
    std::unordered_map<std::string, std::deque<int64_t>> store;
    mutable std::mutex mutex;

public:
    bool try_add(const std::string &key, int64_t window_size, int64_t capacity) override;
    int64_t get_count(const std::string &key) override;
    void remove(const std::string &key) override;
};