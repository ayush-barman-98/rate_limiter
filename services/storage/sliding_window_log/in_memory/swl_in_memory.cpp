#include "services/storage/sliding_window_log/in_memory/swl_in_memory.hpp"
#include "utils/time_utils.hpp"

bool InMemorySlidingWindowLogStorage::try_add(const std::string &key, int64_t window_size, int64_t capacity) {
    int64_t now_sec = utils::getCurrentTimeInSeconds();
    int64_t threshold = now_sec - window_size;

    std::lock_guard<std::mutex> lock(mutex);

    auto &timestamps = store[key];

    while (!timestamps.empty() && timestamps.front() <= threshold) {
        timestamps.pop_front();
    }

    if (timestamps.size() < capacity) {
        timestamps.push_back(now_sec);
        return true;
    }

    // Erase key entry if deque is empty to avoid memory leaks
    if (timestamps.empty()) {
        store.erase(key);
    }

    return false;
}

int64_t InMemorySlidingWindowLogStorage::get_count(const std::string &key) {
    std::lock_guard<std::mutex> lock(mutex);
    auto itr = store.find(key);
    if (itr == store.end()) return 0;
    return static_cast<int64_t>(itr->second.size());
}

void InMemorySlidingWindowLogStorage::remove(const std::string &key) {
    std::lock_guard<std::mutex> lock(mutex);
    store.erase(key);
}
