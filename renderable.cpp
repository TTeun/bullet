#include "renderable.h"
#include "mainview.h"

Renderable::Renderable()
    : coords(new QVector<QVector2D>)
    , colours(new QVector<QVector3D>)
    , indices(new QVector<short int>)
{

}

void Renderable::init(MainView *mainview){
    mainview->glGenVertexArrays(1, &vao);
    mainview->glBindVertexArray(vao);

    mainview->glGenBuffers(1, &coordsBO);
    mainview->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
    mainview->glEnableVertexAttribArray(0);
    mainview->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    mainview->glGenBuffers(1, &coloursBO);
    mainview->glBindBuffer(GL_ARRAY_BUFFER, coloursBO);
    mainview->glEnableVertexAttribArray(1);
    mainview->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


    mainview->glGenBuffers(1, &indicesBO);
    mainview->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBO);

    mainview->glBindVertexArray(0);

}
