#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <QGLWidget>
#include <QTimer>
#include <matrix.h>
#include <vector>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void desenha_cubo(float x, float y, float z, float X, float Y, float Z, float cf1, float cf2, float cf3);
    void desenha_cubo(float x,float y,float z,float X,float Y,float Z);
    void desenha_arestas(float x,float y,float z,float X,float Y,float Z);
    void desenha_eixos();
    void desenha_base();

    int R;
    float x,y,z,x_palete,y_palete,z_palete;
    bool wired,eixos,animacao,base,palete;

    float angulo;
    float a1,a2,a3;
    vector<vector<float>> sol;
    bool resolvido;

private:

    QOpenGLContext* context;
    QOpenGLFunctions *openGLFunctions;
    float rotation;
    QTimer timer;

};

#endif // GLWIDGET_H
