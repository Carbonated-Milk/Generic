#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    void start();
    void stop();
    long long milliseconds();
    long long microseconds();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool is_running = false;
};

inline void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
    is_running = true;
}

inline void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
    is_running = false;
}

inline long long Timer::milliseconds() {
    if (is_running) {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_time).count();
    } else {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }
}

inline long long Timer::microseconds() {
    if (is_running) {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start_time).count();
    } else {
        return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
}

#endif // TIMER_H