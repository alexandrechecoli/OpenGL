#ifndef MEUPAINELOPENGL_H
#define MEUPAINELOPENGL_H

#include <QWidget>
#include <QGLWidget>


class MeuPainelOpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit MeuPainelOpenGL(QWidget *parent = nullptr);

protected: //métodos adicionados
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

signals:

public slots:
    void alterarLados(int l);
    void alterarRaio(double r);



private:
    int lados;
    double raio;
};

#endif // MEUPAINELOPENGL_H
