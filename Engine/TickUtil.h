//
// Created by evans on 29/01/2023.
//

#ifndef R_TYPE_SERVER_TICKUTIL_H
#define R_TYPE_SERVER_TICKUTIL_H

#include <chrono>

class TickUtil {
private:
    unsigned long long currentTick = 0;
    size_t tickTime;
    std::chrono::time_point<std::chrono::system_clock> started;
    std::chrono::time_point<std::chrono::system_clock> tickStart;
public:
    TickUtil(size_t tps);
    void startTick();
    void endTickAndWait();

    void setCurrentTick(unsigned long long int currentTick);

    void setStarted(const std::chrono::time_point<std::chrono::system_clock> &started);

    void setStarted(unsigned long long startms);

    const std::chrono::time_point<std::chrono::system_clock> &getStarted() const;

    unsigned long long int getCurrentTick() const;
};


#endif //R_TYPE_SERVER_TICKUTIL_H
