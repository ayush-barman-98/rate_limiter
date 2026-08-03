#include "fws_in_memory.hpp"
#include "utils/time_utils.hpp"

int64_t InMemoryFixedWindowCounterStorage::increment(const std::string &key, int window_length) {
    int64_t now_sec = utils::getCurrentTimeInSeconds();

    int64_t current_window_time = (now_sec / window_length) * window_length;

    std::lock_guard<std::mutex> lock(mutex);

    auto itr = store.find(key);
    if (itr != store.end()) {
        int64_t last_window_time = itr->second.first;
        if (last_window_time == current_window_time) {
            itr->second.second++;
            return itr->second.second;
        }
    }

    store[key] = { current_window_time, 1 };
    return 1;
}

int64_t InMemoryFixedWindowCounterStorage::get(const std::string &key) {
    std::lock_guard<std::mutex> lock(mutex);
    auto itr = store.find(key);
    if (itr == store.end()) return 0;
    return itr->second.second;
}

void InMemoryFixedWindowCounterStorage::remove(const std::string &key) {
    std::lock_guard<std::mutex> lock(mutex);
    store.erase(key);
}