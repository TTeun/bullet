#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "QVector"
#include "renderable.h"
#include "timer.h"
class Background : public Renderable
{
public:
    Background(Timer *_timer);

    void render(MainView *mainview);
    void update(MainView *mainview);
    void createShader();
    Timer *timer;
private:
    struct star{
        star();
        float intensity;
        float speed;
        float x;
        float y;
    };
    size_t numStars = 130;
    QVector <star> *stars;
};

#endif // BACKGROUND_H
