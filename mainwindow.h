#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_x_valueChanged(double arg1);

    void on_y_valueChanged(double arg1);

    void on_z_valueChanged(double arg1);

    void on_R_valueChanged(double arg1);

    void on_checkBox_clicked(bool checked);

    void on_pushButton_clicked();

    void on_LerDados_clicked();

    void on_Resolver_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_R1_valueChanged(double arg1);

    void on_R2_valueChanged(double arg1);

    void on_R3_valueChanged(double arg1);

    void on_animacao_clicked(bool checked);

    void on_animacao_clicked();

    void on_Eixos_clicked();

    void on_Eixos_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
