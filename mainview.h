#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QOpenGLTexture>
#include "mainwindow.h"
#include "background.h"
#include "timer.h"
#include "ship.h"
#include "vector"

class MainView : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core {

  Q_OBJECT

public:
  MainView(QWidget *Parent = 0);
  ~MainView();
  void updateBuffers();

  Timer *timer;
  Background *bck;
  Ship *shp;

protected:
  void initializeGL();
  void resizeGL(int newWidth, int newHeight);
  void paintGL();

  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent*);
  void wheelEvent(QWheelEvent* event);
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent* event);

private:
  QOpenGLDebugLogger* debugLogger;

  QOpenGLShaderProgram* mainShaderProg;


  void createShaderPrograms();
  void createBuffers();

private slots:
  void onMessageLogged( QOpenGLDebugMessage Message );

};

#endif // MAINVIEW_H
