#ifndef SHIP_H
#define SHIP_H

#include "texturerenderable.h"
#include "QOpenGLTexture"

class Ship : public QObject, public TextureRenderable
{

    Q_OBJECT

public:
    Ship(QWidget *Parent = 0);
    ~Ship() = default;
    void render(MainView *mainview);
    void update(MainView *mainview);
    void createShader();
    GLfloat xpos = 0, ypos = -0.85, xvel = 0, yvel = 0, w = 0.173, h = 0.291, xacc = 0, yacc = 0;

public slots:
    void move(size_t elapsed);


private:
};

#endif // SHIP_H
