#include "timer.h"
#include "QDebug"

Timer::Timer(QWidget *Parent)
    : QObject(Parent)
{
}

Timer::~Timer(){

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

void Timer::checkTicks(){
    std::clock_t currentTime = std::clock() - startTime;
    size_t elapsed = (currentTime) / (((double)CLOCKS_PER_SEC)  * deltaT);

    if (elapsed > 0UL){
        emit ticks(elapsed);
    }
    startTime += elapsed * ((double)CLOCKS_PER_SEC) * deltaT;
}

void Timer::setDeltaT(float _deltaT){
    deltaT = _deltaT;
}
