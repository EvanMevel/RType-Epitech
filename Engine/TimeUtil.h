//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_TIMEUTIL_H
#define R_TYPE_SERVER_TIMEUTIL_H

#include <chrono>
#include <iostream>

long long getCurrentTime();

void preciseSleep(std::chrono::milliseconds);

void preciseSleep(long long sleepMs);

std::ostream &log();

#endif //R_TYPE_SERVER_TIMEUTIL_H
