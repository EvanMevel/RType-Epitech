//
// Created by evans on 24/01/2023.
//

#include "TimeUtil.h"

long long getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}