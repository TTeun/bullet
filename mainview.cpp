#include "mainview.h"

MainView::MainView(QWidget *Parent)
    : QOpenGLWidget(Parent)
    , timer(new Timer())
    , bck(new Background())
    , shp(new Ship())
{

    QObject::connect(timer, SIGNAL(ticks(size_t)), bck, SLOT(updatePositions(size_t)));
    QObject::connect(timer, SIGNAL(ticks(size_t)), shp, SLOT(move(size_t)));

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

  timer->setDeltaT(0.01667);
  timer->start();

  bck->init(this);
  bck->createShader();

  shp->init(this, "../bullet/assets/ship.png");

}

void MainView::resizeGL(int newWidth, int newHeight) {


    qDebug() << ".. resizeGL";
}

void MainView::paintGL() {
    timer->checkTicks();

    glClearColor(0.0, 0.05, 0.10196, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bck->update(this);
    bck->render(this);

    shp->update(this);
    shp->render(this);

}

void MainView::mousePressEvent(QMouseEvent* event) {
    setFocus();

}

void MainView::mouseMoveEvent(QMouseEvent* event) {

}

void MainView::mouseReleaseEvent(QMouseEvent*) {

}

void MainView::wheelEvent(QWheelEvent* event) {
}

void MainView::keyPressEvent(QKeyEvent* event) {
    char key = event->key();
    if (key == 'W')
        shp->yacc++;
    if (key == 'S')
        shp->yacc--;
    if (key == 'A')
        shp->xacc--;
    if (key == 'D')
        shp->xacc++;
}

void MainView::keyReleaseEvent(QKeyEvent* event) {
    char key = event->key();
    if (key == 'W')
        shp->yacc--;
    if (key == 'S')
        shp->yacc++;
    if (key == 'A')
        shp->xacc++;
    if (key == 'D')
        shp->xacc--;
}

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
  qDebug() << " → Log:" << Message;
}
