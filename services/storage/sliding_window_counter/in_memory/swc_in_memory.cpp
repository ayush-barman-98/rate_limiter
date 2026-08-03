#include "services/storage/sliding_window_counter/in_memory/swc_in_memory.hpp"
#include "utils/time_utils.hpp"

bool InMemorySlidingWindowCounterStorage::try_add(const std::string &key , int64_t window_size, int64_t capacity){
    int64_t now_sec = utils::getCurrentTimeInSeconds();
    int64_t current_window = (now_sec / window_size) * window_size;

    std::lock_guard<std::mutex> lock(mutex);

    auto userRequestHistory = store.find(key);
    
    if(userRequestHistory == store.end()){
        // First request by this user.
        int64_t prev_window = current_window - window_size;

        WindowDetails prev_window_details(prev_window, 0), current_window_details(current_window, 1);
        store[key] = {prev_window_details , current_window_details};

        return true;
    }

    auto cache_prev_window = userRequestHistory->second.first;
    auto cache_current_window = userRequestHistory->second.second;

    if(current_window > cache_current_window.time_stamp + window_size){
        // A window was skipped, so replace both old windows.
        // Here , W2] - [W1] = [W3] - [W4] = [W3] - [W2] = window_size
        // [W1] , [W2] , [W3] , [W4] --> The cache had [W1] and [W2] 
        // as current_window > W3 , it has to be something >= W4

        WindowDetails new_curr_window(current_window , 1) , new_prev_window(current_window - window_size , 0);

        store[key] = {new_prev_window , new_curr_window};

    }else if(current_window  == cache_current_window.time_stamp + window_size){
        // The request belongs to [W3] window

        double curr_window_fraction = static_cast<double>(now_sec - current_window) / window_size;
        double effective_total_requests = 1 + (1 - curr_window_fraction) * cache_current_window.request_count;

        if(effective_total_requests > (double)capacity) return false;

        WindowDetails new_curr_window(current_window ,1);
        store[key] = {cache_current_window , new_curr_window};

    }else if(current_window == cache_current_window.time_stamp){
        // This request belongs to [W2] window

        double curr_window_fraction = static_cast<double>(now_sec - current_window) / window_size;
        double effective_total_requests = (cache_current_window.request_count + 1) + (1 - curr_window_fraction) * cache_prev_window.request_count;

        if(effective_total_requests > (double)capacity) return false;

        store[key].second.request_count += 1;

    }
    return true;

}

double InMemorySlidingWindowCounterStorage::get_estimated_count(const std::string &key, int64_t window_size){

    // There is no request coming up here, we are just 
    // checking the current allowed capacity for that user. 

    int64_t now_sec = utils::getCurrentTimeInSeconds();
    int64_t current_window = (now_sec / window_size) * window_size;


    std::lock_guard<std::mutex> lock(mutex);

    auto userRequestHistory = store.find(key);
    if(userRequestHistory == store.end()) return 0.0;

    auto cache_prev_window = userRequestHistory->second.first;
    auto cache_current_window = userRequestHistory->second.second;

    double curr_window_fraction = static_cast<double>(now_sec - current_window) / window_size;

    double effective_total_requests = static_cast<double>(cache_current_window.request_count) + cache_prev_window.request_count * (1 - curr_window_fraction);

    return effective_total_requests;

}


void InMemorySlidingWindowCounterStorage::remove(const std::string &key){
    std::lock_guard<std::mutex> lock(mutex);
    store.erase(key);
    return;
}