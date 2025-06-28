#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <functional>
using namespace std;

/*
 * === PART 1: addTimer(...) ===
 *
 * In the real system, we only have:
 *   void setTimer(long durationMillis, Runnable callback);
 *   long getCurrentTimeMillis();
 *
 * We want to implement:
 *
 *   // Wait durationMillis ms, then run callback.
 *   // Supports multiple concurrent timers.
 *   void addTimer(long durationMillis, function<void()> callback);
 *
 * Under time pressure, a minimal correct‐semantics version spawns one detached
 * thread per call, sleeps the full duration, then invokes the callback.
 */
void addTimer(long durationMillis, function<void()> callback) {
    // TODO: spawn a detached thread that sleeps and then runs callback

}

/*
 * Demo/Test harness for addTimer.
 * We schedule two overlapping timers and print timestamps to verify both fire.
 */
int testAddTimer() {
    auto start = chrono::steady_clock::now();
    auto rel = [&]() {
        return chrono::duration_cast<chrono::milliseconds>(
                chrono::steady_clock::now() - start
        ).count();
    };

    cout << "[" << rel() << " ms] schedule A(100)\n";
    addTimer(100, [=]() {
        cout << "[" << rel() << " ms] fired A(100)\n";
    });

    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "[" << rel() << " ms] schedule B(50)\n";
    addTimer(50, [=]() {
        cout << "[" << rel() << " ms] fired B(50)\n";
    });

    // Give time for both callbacks to fire
    this_thread::sleep_for(chrono::milliseconds(200));
    return 0;
}


/*
 * Combined main(): call both demos in sequence.
 */
int main() {
    cout << "=== Test addTimer ===\n";
    testAddTimer();
}