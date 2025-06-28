#include <thread>
#include <chrono>
#include <functional>

/// addTimer: spawn a detached thread, sleep for durationMillis, then run callback.
/// This does *not* cancel or overwrite any previous timers.
void addTimer(long durationMillis, std::function<void()> callback) {
    std::thread([durationMillis, callback]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationMillis));
        callback();
    }).detach();
}

// --------------------------------------------
// (Optional) Demo for addTimer:
#include <iostream>
#include <atomic>

int main() {
    // A small “clock” to measure relative ms from program start:
    auto start = std::chrono::steady_clock::now();
    auto rel = [&]() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start
        ).count();
    };

    std::cout << "[" << rel() << " ms] scheduling A(100)\n";
    addTimer(100, [=]() {
        std::cout << "[" << rel() << " ms] fired A(100)\n";
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "[" << rel() << " ms] scheduling B(50)\n";
    addTimer(50, [=]() {
        std::cout << "[" << rel() << " ms] fired B(50)\n";
    });

    // Give them time to fire:
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return 0;
}