#include "meupainelopengl.h"

MeuPainelOpenGL::MeuPainelOpenGL(QWidget *parent) : QGLWidget(parent)
{
    setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    lados = 3;
    raio = 1.0;
}
void initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f,1.0f,1.0f,0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

}

void MeuPainelOpenGL::resizeGL(int width, int height)
{
   double menorX = 0, maiorX = 10, menorY = 0, maiorY = 10;
   glViewport(0,0,(GLint)width, (GLint)height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho2D(-1,1,-1,1);
   glo



}
void MeuPainelOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MeuPainelOpenGL::alterarLados(int l)
{
    if (lados != l && l >= 3 && l <= 60)
    {
        lados = l;
        updateGL();
    }

}
void MeuPainelOpenGL::alterarRaio(double r)
{
    if(raio != r && r>=1.0 && r<= 5.0)
    {
        raio =r;
        updateGL();
    }

}
