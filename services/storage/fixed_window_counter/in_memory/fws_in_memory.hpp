#pragma once
#include "fws_interface.hpp"
#include <unordered_map>
#include <mutex>
#include <utility>

class InMemoryFixedWindowCounterStorage : public IFixedWindowCounterStorage {
private:
    // { user_identifier -> { window_start_time , reqCount } }
    std::unordered_map<std::string, std::pair<int64_t, int64_t>> store;
    mutable std::mutex mutex;

public:
    int64_t increment(const std::string &key, int window_size) override;
    int64_t get(const std::string &key) override;
    void remove(const std::string &key) override;
};