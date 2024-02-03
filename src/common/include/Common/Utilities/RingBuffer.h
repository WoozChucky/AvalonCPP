#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include "Common/Logging/Log.h"
#include "Optional.h"

template<typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity) : capacity(capacity) {}

    void Enqueue(T item) {
        std::unique_lock<std::mutex> lock(mtx);

        while(queue.size() >= capacity) {
            auto start = std::chrono::high_resolution_clock::now();
            cv.wait(lock);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            LOG_TRACE("network", "Time spent waiting: {}ms", elapsed.count());
        }

        queue.push(std::move(item));
        cv.notify_one();
    }

    Optional<T> Dequeue() {
        std::unique_lock<std::mutex> lock(mtx);

        while(queue.empty() && !stopDequeue) {
            cv.wait(lock);
        }

        if (stopDequeue) {
            return std::nullopt;
        }

        T item = std::move(queue.front());
        queue.pop();
        cv.notify_one();

        return item;
    }

    void StopDequeue() {
        stopDequeue = true;
        cv.notify_all(); // Wake up any threads waiting on the condition variable
    }

private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    size_t capacity;
    std::atomic<bool> stopDequeue;
};
