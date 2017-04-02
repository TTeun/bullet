#ifndef SHIP_H
#define SHIP_H

#include "texturerenderable.h"
#include "QOpenGLTexture"

class Ship : public TextureRenderable
{
public:
    Ship();
    void render(MainView *mainview);
    void update(MainView *mainview);
    void createShader();
    void initTexture(MainView *mainview);

private:
};

#endif // SHIP_H
