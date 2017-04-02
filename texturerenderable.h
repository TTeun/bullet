#ifndef TEXTURERENDERABLE_H
#define TEXTURERENDERABLE_H

#include "renderable.h"


class TextureRenderable : public Renderable
{
public:
    TextureRenderable();
    void init(MainView *mainview);

protected:
    GLuint texture;
    GLuint texBO;
    QVector<QVector2D> *texCoords;

};

#endif // TEXTURERENDERABLE_H
