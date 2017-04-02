#include "texturerenderable.h"
#include "mainview.h"
#include "SOIL/SOIL.h"

TextureRenderable::TextureRenderable()
    : texCoords(new QVector<QVector2D>)
{

}

void TextureRenderable::init(MainView *mainview){
    createShader();

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

    mainview->glBindVertexArray(vao);

    mainview->glGenBuffers(1, &texBO);
    mainview->glBindBuffer(GL_ARRAY_BUFFER, texBO);
    mainview->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    mainview->glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height;
    unsigned char* image = SOIL_load_image("../bullet/assets/player.png", &width, &height, 0, SOIL_LOAD_RGBA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);



}
