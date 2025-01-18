#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <condition_variable>
#include <mutex>

class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore(int init_count) : count(init_count) {}

    void P() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        --count;
    }

    void V() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            ++count;
        }
        cv.notify_one();
    }
};

#endif // SEMAPHORE_H