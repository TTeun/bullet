#include "timer.h"
#include "QDebug"

Timer::Timer(float _deltaT){
    deltaT = _deltaT;
}

void Timer::start()
{
    startTime = std::clock();
};

bool Timer::ticked()
{
    std::clock_t currentTime = std::clock();

    if ((currentTime - startTime) > ((double)CLOCKS_PER_SEC)  * deltaT)
    {
        startTime += ((double)CLOCKS_PER_SEC) * deltaT;
        return true;
    }
    return false;
}

size_t Timer::ticksPassed(){
    std::clock_t currentTime = std::clock() - startTime;
    size_t elapsed = (currentTime) / (((double)CLOCKS_PER_SEC)  * deltaT);
    startTime += elapsed * ((double)CLOCKS_PER_SEC) * deltaT;
    return elapsed;
}
