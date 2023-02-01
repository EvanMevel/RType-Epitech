//
// Created by evans on 29/01/2023.
//

#include <thread>
#include <iostream>
#include "TickUtil.h"
#include "TimeUtil.h"

TickUtil::TickUtil(size_t tps) {
    started = std::chrono::system_clock::now();
    tickTime = 1000 / tps;
}

void TickUtil::startTick() {
    tickStart = std::chrono::system_clock::now();
    currentTick++;
}

void TickUtil::endTickAndWait() {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - tickStart).count();

    //std::cout << "Tick took " << elapsed << "ms" << std::endl << std::flush;

    auto waiting = tickTime - elapsed;
    if (waiting > 0) {
        auto timeStarted = std::chrono::duration_cast<std::chrono::milliseconds>(now - started).count();
        auto shouldBe = timeStarted / tickTime;
        if (shouldBe <= currentTick) {
            auto mswaiting = std::chrono::milliseconds(waiting);
            preciseSleep(mswaiting);
        }
        /*else {
            auto ticksBehind = shouldBe - currentTick;
            std::cout << "Server is " << ticksBehind << " ticks behind " << currentTick << "  " << shouldBe << std::endl << std::flush;
        }*/
    }
}

void TickUtil::setCurrentTick(unsigned long long int ct) {
    TickUtil::currentTick = ct;
}

void TickUtil::setStarted(const std::chrono::time_point<std::chrono::system_clock> &started) {
    TickUtil::started = started;
}

void TickUtil::setStarted(unsigned long long startms) {
    TickUtil::started = std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(startms));
}

unsigned long long int TickUtil::getCurrentTick() const {
    return currentTick;
}

const std::chrono::time_point<std::chrono::system_clock> &TickUtil::getStarted() const {
    return started;
}
