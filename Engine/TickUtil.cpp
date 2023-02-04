// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
