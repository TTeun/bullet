#include "mainview.h"

MainView::MainView(QWidget *Parent)
    : QOpenGLWidget(Parent)
    , timer(new Timer(0.0166667))
    , bck(new Background(timer))
    , shp(new Ship())
{

}

MainView::~MainView() {
  qDebug() << "✗✗ MainView destructor";

  debugLogger->stopLogging();

  delete mainShaderProg;
}

// ---

void MainView::createShaderPrograms() {
  qDebug() << ".. createShaderPrograms";

  // Main shader program
  mainShaderProg = new QOpenGLShaderProgram();
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

  mainShaderProg->link();


}

void MainView::createBuffers() {

}

void MainView::initializeGL() {

  initializeOpenGLFunctions();
  qDebug() << ":: OpenGL initialized";

  debugLogger = new QOpenGLDebugLogger();
  connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

//  if ( debugLogger->initialize() ) {
//    qDebug() << ":: Logging initialized";
//    debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
//    debugLogger->enableMessages();
//  }

  QString glVersion;
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

  // Enable depth buffer
  glEnable(GL_DEPTH_TEST);
  // Default is GL_LESS
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_TEXTURE_2D);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  createShaderPrograms();
  createBuffers();

  timer->start();

  bck->init(this);
  bck->createShader();

  shp->init(this);

}

void MainView::resizeGL(int newWidth, int newHeight) {
  qDebug() << ".. resizeGL";
}

void MainView::paintGL() {
    glClearColor(0.0, 0.05, 0.10196, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bck->update(this);
    bck->render(this);

    shp->update(this);
    shp->render(this);

}

void MainView::mousePressEvent(QMouseEvent* event) {}

void MainView::mouseMoveEvent(QMouseEvent* event) {}

void MainView::mouseReleaseEvent(QMouseEvent*) {
  setFocus();
}

void MainView::wheelEvent(QWheelEvent* event) {
}

void MainView::keyPressEvent(QKeyEvent* event) {
  switch(event->key()) {
  case 'Z':

      update();
    break;
  }
}

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
  qDebug() << " → Log:" << Message;
}
