#include "renderable.h"
#include "background.h"
#include "mainview.h"
#include "qglobal.h"
#include "QTime"

Background::star::star(){
    intensity = (qrand() % 255) / 255.0f;
    speed = (qrand() % 100) / 4000.0f + 0.001f;
    x = -1 + ((qrand() % 200) / 100.0f);
    y = -1 + ((qrand() % 200) / 100.0f);
}

Background::Background(QWidget *Parent)
    : QObject(Parent)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    stars = new QVector<star> (numStars);

    colours->clear();
    colours->squeeze();
    for (size_t i = 0; i < numStars; ++i)
        colours->append(QVector3D( (*stars)[i].intensity, (*stars)[i].intensity, (*stars)[i].intensity ));

    coords->clear();
    coords->squeeze();
    for (size_t i = 0; i < numStars; ++i)
        coords->append(QVector2D((*stars)[i].x, (*stars)[i].y));

}

void Background::render(MainView *mainview){
    shaderProg->bind();
    mainview->glBindVertexArray(vao);
    mainview->glPointSize(2);
    mainview->glDrawArrays(GL_POINTS, 0, numStars);
    shaderProg->release();
}

void Background::updatePositions(size_t ticksPassed){
    for (size_t i = 0; i < numStars; ++i){
        (*coords)[i][1] -= ticksPassed * (*stars)[i].speed;
        if ((*coords)[i][1] < -1.0f){
            (*stars)[i] = star();
            (*stars)[i].y = 1.0f;
            (*coords)[i] = QVector2D((*stars)[i].x, (*stars)[i].y);
        }
    }

}

void Background::update(MainView *mainview){


    mainview->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
    mainview->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*coords->size(), coords->data(), GL_DYNAMIC_DRAW);

    mainview->glBindBuffer(GL_ARRAY_BUFFER, coloursBO);
    mainview->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*colours->size(), colours->data(), GL_DYNAMIC_DRAW);

    mainview->update();
}

void Background::createShader(){
    // Main shader program
    shaderProg = new QOpenGLShaderProgram();
    shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

    shaderProg->link();
}
