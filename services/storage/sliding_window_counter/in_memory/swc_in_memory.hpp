#pragma once

#include "services/storage/sliding_window_counter/swc_interface.hpp"
#include <unordered_map>
#include <utility>
#include <mutex>
#include <string>
#include <cstdint>

using std::pair;

struct WindowDetails {
    int64_t time_stamp{0};
    int64_t request_count{0};
    WindowDetails(int64_t ts = 0, int64_t count = 0)
        : time_stamp(ts), request_count(count) {}
};

class InMemorySlidingWindowCounterStorage : public ISlidingWindowCounterStorage {
private:
    std::unordered_map<std::string, pair<WindowDetails, WindowDetails>> store;
    mutable std::mutex mutex;

public:
    bool try_add(const std::string &key, int64_t window_size, int64_t capacity) override;
    double get_estimated_count(const std::string &key, int64_t window_size) override;
    void remove(const std::string &key) override;
};