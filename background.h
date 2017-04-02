#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "QVector"
#include "renderable.h"
#include "timer.h"
#include "QObject"

class Background : public QObject, public Renderable
{
    Q_OBJECT

public:
    Background(QWidget *Parent = 0);
    ~Background() = default;

    void render(MainView *mainview);
    void update(MainView *mainview);
    void createShader();

public slots:
    void updatePositions(size_t ticksPassed);

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
