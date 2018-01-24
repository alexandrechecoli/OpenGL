#include "glwidget.h"
#include <QOpenGLWindow>
#include <GL/glut.h>
#include <QMessageBox>

GLWidget::GLWidget(QWidget *parent)
{
    this->R=1;
    this->wired = false;
    this->angulo = 0.5;
    connect( &timer, SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
    resolvido = false;
    a1=a2=a3=1;
    animacao = false;
    palete = false;
    eixos = false;
}

void GLWidget::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,0.5,  0,0,0,  0,1,0);

if(animacao)
    angulo+=0.5;



    glTranslatef(x,y,z);
    glRotatef(angulo,a1,a2,a3);


    glColor3f(1,1,1);


    float x,y,z,X,Y,Z;
    x=y=z=0;
    X=1;
    Y=1;
    Z=1;

    if(resolvido){

    if(eixos)
        desenha_eixos();
    if(palete)
        desenha_base();

    for(int i=0;i<sol.size();i++)
    {
        x=(float)sol[i][0]; y=(float)sol[i][1];z=(float)sol[i][2];
        X=sol[i][3]; Y=(float)sol[i][4];Z=(float)sol[i][5];
/*
    x=x/20;
    y=y/20;
    z=z/20;
    X=X/20;
    Y=Y/20;
    Z=Z/20;
*/

    if(wired)
    {
        desenha_arestas(x,y,z,X,Y,Z);
    }else{
        desenha_arestas(x,y,z,X,Y,Z);
        desenha_cubo(x,y,z,X,Y,Z);
    }

    }
    }



}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(float)w/h,0.01,100.0);

    updateGL();
}

void GLWidget::desenha_cubo(float x,float y,float z,float X,float Y,float Z)
{

    float cf1,cf2,cf3,cl1,cl2,cl3,inc; //cor da face
    cf1=cf2=cf3=1.0;
    cl1=cl2=cl3=0.0;

    //FACE 1 + ARESTAS DA FACE 1

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z);
        glVertex3f(x + X,y,z);
        glVertex3f(x + X,y + Y,z);
        glVertex3f(x,y + Y,z);
    glEnd();


    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z);
        glVertex3f(x+X,y,z);
        glVertex3f(x+X,y,z+Z);
        glVertex3f(x,y,z+Z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z);
        glVertex3f(x,y+Y,z);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x,y,z+Z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x+X,y,z);
        glVertex3f(x+X,y+Y,z);
        glVertex3f(x+X,y+Y,z+Z);
        glVertex3f(x+X,y,z+Z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y+Y,z);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z+Z);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z+Z);
        glVertex3f(x+X,y,z+Z);
    glEnd();





}

void GLWidget::desenha_cubo(float x,float y,float z,float X,float Y,float Z,float cf1, float cf2, float cf3)
{
    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z);
        glVertex3f(x + X,y,z);
        glVertex3f(x + X,y + Y,z);
        glVertex3f(x,y + Y,z);
    glEnd();


    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z);
        glVertex3f(x+X,y,z);
        glVertex3f(x+X,y,z+Z);
        glVertex3f(x,y,z+Z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z);
        glVertex3f(x,y+Y,z);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x,y,z+Z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x+X,y,z);
        glVertex3f(x+X,y+Y,z);
        glVertex3f(x+X,y+Y,z+Z);
        glVertex3f(x+X,y,z+Z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y+Y,z);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(cf1,cf2,cf3); //cor do vertice
        glVertex3f(x,y,z+Z);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z+Z);
        glVertex3f(x+X,y,z+Z);
    glEnd();

}


void GLWidget::desenha_arestas(float x,float y,float z,float X,float Y,float Z)
{

    float cl1,cl2,cl3,inc; //cor da face

    cl1=cl2=cl3=0.0;
    glLineWidth(2.5);
    glColor3f(cl1,cl2,cl3); //cor do vertice

    glBegin(GL_LINES);
        glVertex3f(x,y,z);
        glVertex3f(x + X,y,z);
    glEnd();
    glBegin(GL_LINES);
         glVertex3f(x + X,y,z);
        glVertex3f(x + X,y + Y,z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x + X,y + Y,z);
        glVertex3f(x,y + Y,z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x,y + Y,z);
        glVertex3f(x,y,z);
    glEnd();


    glBegin(GL_LINES);
         glVertex3f(x,y,z);
        glVertex3f(x+X,y,z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y,z);;
        glVertex3f(x+X,y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y,z+Z);
       glVertex3f(x,y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x,y,z+Z);
        glVertex3f(x,y,z);
    glEnd();


    glBegin(GL_LINES);
         glVertex3f(x,y,z);
        glVertex3f(x,y+Y,z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x,y+Y,z);
        glVertex3f(x,y+Y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x,y+Y,z+Z);
       glVertex3f(x,y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x,y,z+Z);
        glVertex3f(x,y,z);
    glEnd();

    glBegin(GL_LINES);
         glVertex3f(x+X,y,z);
        glVertex3f(x+X,y+Y,z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y+Y,z);
        glVertex3f(x+X,y+Y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y+Y,z+Z);
       glVertex3f(x+X,y,z+Z);;
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y,z+Z);;
        glVertex3f(x+X,y,z);
    glEnd();

    glBegin(GL_LINES);
         glVertex3f(x,y+Y,z);
        glVertex3f(x,y+Y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x,y+Y,z+Z);
        glVertex3f(x+X,y+Y,z+Z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y+Y,z+Z);
       glVertex3f(x+X,y+Y,z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(x+X,y+Y,z);
        glVertex3f(x,y+Y,z);
    glEnd();
    glFlush();

}

void GLWidget::desenha_eixos()
{
    glLineWidth(3);

    glColor3f(1,0,0); //cor do vertice
    glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,50);
    glEnd();

    glColor3f(0,0,1); //cor do vertice
    glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,50.0,0);
    glEnd();
    glColor3f(0,0,1); //cor do vertice
    glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(50.0,0.0,0);
    glEnd();

}

void GLWidget::desenha_base()
{
    desenha_arestas(0,0,0,x_palete,y_palete,-0.5);
    desenha_cubo(0,0,0,x_palete,y_palete,-0.5,0,0,0);
}

