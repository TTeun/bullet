#ifndef TEXTURERENDERABLE_H
#define TEXTURERENDERABLE_H

#include "renderable.h"
#include "vector"

class TextureRenderable : public Renderable
{
public:
    TextureRenderable();
    void init(MainView *mainview, const char* path);
    void setPath(std::vector<char> str);

protected:
    GLuint texture;
    GLuint texBO;
    QVector<QVector2D> *texCoords;
    std::vector<char> path;
};

#endif // TEXTURERENDERABLE_H
