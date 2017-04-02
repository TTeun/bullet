#ifndef TIMER__H
#define TIMER__H

#include <iostream>
#include <ctime>

class Timer {
public:
    Timer() = default;
    Timer(float _deltaT);
    void start();
    bool ticked();
    size_t ticksPassed();


private:
    std::clock_t startTime;
    std::clock_t tickTime;
    float deltaT = 1.0;


};

#endif
