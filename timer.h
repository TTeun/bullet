#ifndef TIMER__H
#define TIMER__H

#include <iostream>
#include <ctime>
#include "QObject"
#include <QOpenGLWidget>


class Timer : public QObject {

    Q_OBJECT

public:
    Timer(QWidget *Parent = 0);
    ~Timer();

    void setDeltaT(float _deltaT);
    void start();
    bool ticked();
    void checkTicks();

signals:
    void ticks(size_t numTicks);

private:
    std::clock_t startTime;
    std::clock_t tickTime;
    float deltaT = 1.0;
};

#endif
