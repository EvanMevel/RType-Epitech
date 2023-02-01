//
// Created by evans on 24/01/2023.
//

#include <thread>
#include "TimeUtil.h"

long long getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

void preciseSleep(std::chrono::milliseconds sleepMs) {
    auto start = std::chrono::high_resolution_clock::now();
    auto oneMs = std::chrono::milliseconds(1);

    while (true) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed >= sleepMs) {
            break;
        }
        std::this_thread::sleep_for(oneMs);
    }
}

void preciseSleep(long long sleepMs) {
    preciseSleep(std::chrono::milliseconds(sleepMs));
}