#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "QVector"
#include "QVector2D"
#include "QVector3D"
#include "QOpenGLShaderProgram"

class MainView;

class Renderable
{
public:
    Renderable();
    unsigned int vao, coordsBO, coloursBO, indicesBO;

    QOpenGLShaderProgram *shaderProg;
    QVector<QVector2D> *coords;
    QVector<QVector3D> *colours;
    QVector<short int> *indices;

    virtual void init(MainView *mainview);
    virtual void render(MainView *mainview) = 0;
    virtual void update(MainView *mainview) = 0;
    virtual void createShader() = 0;
};

#endif // RENDERABLE_H
