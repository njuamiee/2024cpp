#include "Concurrency.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>

int sum = 0;
std::mutex sum_mtx;

void increment() {
    std::lock_guard<std::mutex> lock(sum_mtx);
    ++sum;
}

std::atomic<int> atomic_sum(0);

void init_sum(int value) {
    atomic_sum.store(value);
}

void atomic_increment(int v) {
    atomic_sum.fetch_add(v, std::memory_order_relaxed);
}

std::mutex bracket_mtx;
std::condition_variable cv;
std::string brackets;
int open_count = 0;  // 当前未匹配的左括号数

void produce(int k) {
    std::unique_lock<std::mutex> lock(bracket_mtx);
    cv.wait(lock, [k]() { return open_count < k; });
    brackets.push_back('(');
    ++open_count;
    cv.notify_all();
}

void consume([[maybe_unused]] int k) {
    std::unique_lock<std::mutex> lock(bracket_mtx);
    cv.wait(lock, []() { return open_count > 0; });
    brackets.push_back(')');
    --open_count;
    cv.notify_all();
}

void slow_increment(int times) {
    for (int i = 0; i < times; ++i) {
        increment();
    }
}

void quick_increment(int times, int v) {
    for (int i = 0; i < times; ++i) {
        atomic_increment(v);
    }
}

void producer_thread(int times, int k) {
    for (int i = 0; i < times; ++i) {
        produce(k);
    }
}

void consumer_thread(int times, int k) {
    for (int i = 0; i < times; ++i) {
        consume(k);
    }
}
