#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>


//modificação para testar o commit
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


