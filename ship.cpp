#include "ship.h"
#include "mainview.h"

Ship::Ship()
{
    coords->clear();
    coords->squeeze();
    coords->append(QVector2D(-0.05, -0.9));
    coords->append(QVector2D(-0.05, -0.8));
    coords->append(QVector2D(0.05, -0.8));
    coords->append(QVector2D(0.05, -0.9));

    texCoords->clear();
    texCoords->squeeze();
    texCoords->append(QVector2D(0.0, 0.0));
    texCoords->append(QVector2D(0.0, 1.0));
    texCoords->append(QVector2D(1.0, 1.0));
    texCoords->append(QVector2D(1.0, 0.0));

    colours->clear();
    colours->squeeze();
    for (size_t i = 0; i < 4; ++i)
        colours->append(QVector3D(0.6,0.6,0.6));

}

void Ship::update(MainView *mainview){
    int location = shaderProg->uniformLocation("ourTexture");;
    shaderProg->setUniformValue(location, 0);


    mainview->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
    mainview->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*coords->size(), coords->data(), GL_DYNAMIC_DRAW);

    mainview->glBindBuffer(GL_ARRAY_BUFFER, coloursBO);
    mainview->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*colours->size(), colours->data(), GL_DYNAMIC_DRAW);

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
