#include "ship.h"
#include "mainview.h"
#include "QtGlobal"

Ship::Ship(QWidget *Parent)
    : QObject(Parent)
{
    texCoords->clear();
    texCoords->squeeze();
    texCoords->append(QVector2D(0.0, 0.0));
    texCoords->append(QVector2D(0.0, 1.0));
    texCoords->append(QVector2D(1.0, 1.0));
    texCoords->append(QVector2D(1.0, 0.0));

    colours->clear();
    colours->squeeze();
}

void Ship::update(MainView *mainview){
    int location = shaderProg->uniformLocation("ourTexture");;
    shaderProg->setUniformValue(location, 0);

    coords->clear();
    coords->squeeze();
    coords->append(QVector2D(xpos - w / 2, ypos - h / 2));
    coords->append(QVector2D(xpos - w / 2, ypos + h / 2));
    coords->append(QVector2D(xpos + w / 2, ypos + h / 2));
    coords->append(QVector2D(xpos + w / 2, ypos - h / 2));

    mainview->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
    mainview->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*coords->size(), coords->data(), GL_DYNAMIC_DRAW);

    mainview->glBindBuffer(GL_ARRAY_BUFFER, texBO);
    mainview->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*texCoords->size(), texCoords->data(), GL_DYNAMIC_DRAW);

    mainview->update();
}

void Ship::render(MainView *mainview){

    shaderProg->bind();
    mainview->glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);

    int location = shaderProg->uniformLocation("ourTexture");;
    shaderProg->setUniformValue(location, 0);
    mainview->glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    shaderProg->release();

}

void Ship::createShader(){
    // Main shader program
    shaderProg = new QOpenGLShaderProgram();
    shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vert_tex.glsl");
    shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag_tex.glsl");

    shaderProg->link();
}

void Ship::move(size_t elapsed){

    if (xacc)
        xvel += 0.3 * xacc;
    else
        xvel /= 2;

    if (yacc)
        yvel += 0.3 * yacc;
    else
        yvel /= 2;


    xvel = qBound(-3.9f, xvel, 3.9f);
    yvel = qBound(-3.9f, yvel, 3.9f);



    xpos += 0.01 * elapsed * xvel;
    ypos += 0.01 * elapsed * yvel;

    ypos = qBound(-1.0f + 0.6f * h, ypos, 1.0f - 0.6f * h);
    xpos = qBound(-1.0f + 0.6f * w, xpos, 1.0f - 0.6f * w);
}
