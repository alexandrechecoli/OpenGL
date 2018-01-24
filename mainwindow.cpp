#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <matrix.h>
#include <packing3d.h>
#include <fstream>
#include <mar.h>
#include <random>
#include <stdio.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <qfiledialog.h>
#include <QMessageBox>

using namespace std;

matrix solucao;
map <int, vector<vector<int>>> h1;
int x_palete,y_palete,z_palete;

matrix caixas;
vector<int> qtde_caixas;
vector<int> tipo_caixas;


void ler_dados(int &x, int &y, int &z, matrix &m, vector<int> &tipos_caixas, vector<int>&qtde_caixas, string caminho,  map <int, vector<vector<int>>> &r_posicoes);
vector<double> resolve_batelada(string caminho);
void imprime_indicadores(vector<vector<double>> indicadores, vector<string> nomes);
void gera_instancia(int x, int y, int z, int tipos_caixas, string caminho_nome, int numero_pontos);
void gera_instancia(int x, int y, int z, int tipos_caixas, string caminho_nome, int numero_pontos,int massa_minima,int massa_maxima,
                    int carga_minima, int carga_maxima);
void gera_instancia(int x, int y, int z, int tipos_caixas, string caminho_nome, int numero_pontos,int massa_minima,int massa_maxima,
                    int carga_minima, int carga_maxima, int min_caixas_restritas, int max_caixas_restritas, int min_restricoes_por_caixas,
                    int max_restricoes_caixa);

void exporta_indicadores(vector<vector<double>> indicadores, vector<string> nomes);


void ler_dados(int &x, int &y, int &z, matrix &m, vector<int> &tipos_caixas, vector<int> &qtde_caixas, string caminho, map<int, vector<vector<int> > > &r_posicoes)
{
    ifstream f;
    //f.open("/home/alexandre/Documentos/Programas_c++/3D_PACKING/data/data_3.txt",ifstream::in);
    //const char[] c_caminho = caminho;

    f.open(caminho,ifstream::in);
    int n_tipos_caixas = 0;
    int qtde_pontos = 0;
    f >> n_tipos_caixas;
    f >> qtde_pontos;
    f >> x; f >> y; f >> z;

    m.redim(n_tipos_caixas,6);

    for(int i=0;i<n_tipos_caixas;i++)
    {
        f >> m[i][0];
        f >> m[i][1];
        f >> m[i][2];
        int volume = (int)m[i][0]*(int)m[i][1]*(int)m[i][2];
        m[i][3] = volume;
        f >> m[i][4];
        f >> m[i][5];
    }
    int a;
    int b;
    for(int i = 0;i < qtde_pontos;i++)
    {
        f >> a;
        f >> b;
        qtde_caixas.push_back(a);
        tipos_caixas.push_back(b);
    }

    //lendo as restrições de posicionamento das caixas;
    int numero_caixas_restritas = 0;
    int tipo_caixa_restrita = 0;
    int n_restricoes = 0;

    f >> numero_caixas_restritas;
    for(int i=0;i<numero_caixas_restritas;i++)
    {
        f >> tipo_caixa_restrita;
        f >> n_restricoes;
        vector<vector<int>> vv;
        for(int j=0;j<n_restricoes;j++)
        {
            vector<int> v;
            int x,y,z;
            f >> x ;f >> y;f >> z;
            v.push_back(x);v.push_back(y);v.push_back(z);
            vv.push_back(v);
        }
        r_posicoes[tipo_caixa_restrita] = vv;
    }



    f.close();

}

vector<double> resolve_batelada(string caminho)
{
    map <int, vector<vector<int>>> h1;
    int x_palete,y_palete,z_palete;
    x_palete = y_palete = z_palete = 0;
    matrix caixas;
    vector<int> qtde_caixas;
    vector<int> tipo_caixas;
    ler_dados(x_palete,y_palete,z_palete,caixas,tipo_caixas,qtde_caixas,caminho,h1);
    //caixas.print();
    packing3D p(x_palete,y_palete,y_palete,caixas,h1);
    p.pack(tipo_caixas,qtde_caixas);
    //matrix resultado(1,1);
   //vector<vector<int>>resultado = p.getSolucaoV();
    matrix sol = p.getSolucao();
    sol.print();
    vector<double> indicadores;
    indicadores = p.getIndicadores();
    return indicadores;

   /* cout << "Aproveitamento palete : "<< indicadores[0]*100 << "%\n";
    cout << "Aproveitamento Vol. caixas : "<< indicadores[1]*100 <<"%\n";
    cout << "Aproveitamento qtde. caixas : " << indicadores[2]*100 <<"%\n";
    cout << "Caixas empacotadas : " << indicadores[4] <<"\n";
    cout << "Total de caixas : " << indicadores[3] << "\n\n";*/

}

void imprime_indicadores(vector<vector<double>> indicadores, vector<string> nomes)
{
    for(int i=0;i<indicadores.size();i++)
    {
        string nome = nomes[i];
        nome = nome.erase(0,57);
        cout << nome << "\n";
        cout << "Aproveitamento Vol. palete : "<< indicadores[i][0]*100 << "%\n";
        cout << "Aproveitamento Vol. caixas : "<< indicadores[i][1]*100 <<"%\n";
        cout << "Aproveitamento Qtde. caixas : " << indicadores[i][2]*100 <<"%\n";
        cout << "Caixas empacotadas : " << indicadores[i][4] <<"\n";
        cout << "V. palet/ V. caixas : " << indicadores[i][5]*100 <<"%\n";
        cout << "Total de caixas : " << indicadores[i][3] << "\n\n";
    }
}


void exporta_indicadores(vector<vector<double>> v, vector<string> nomes)
{

    ofstream escritor("/home/alexandre/Documentos/Programas_c++/3D_PACKING/indicadores/resultados_1_4.txt");
    escritor << "Instancia;Aproveitamento Vol. palete" << ";" << "Aproveitamento Vol. caixas" << ";" << "Aproveitamento Qtde. caixas" << ";" << "Caixas empacotadas" << ";" << "V. palet/ V. caixas" << ";" << "Total de caixas" << "\n" ;
    for(int i=0;i<v.size();i++)
    {
        string nome = nomes[i];
        nome = nome.erase(0,70);
        escritor << nome<< ";" << v[i][0] << ";" << v[i][1] << ";" << v[i][2] << ";" << v[i][4] << ";" << v[i][5] << ";" << v[i][3] << "\n" ;
    }
    escritor.close();
}

void gera_instancia(int x, int y, int z, int tipos_caixas, string caminho_nome, int numero_pontos
                    )
{
    random_device r;
    int max_dim = 0;
    int volume_palete = (int)x*(int)y*(int)z;
    int volume_por_ponto = round(volume_palete/numero_pontos);
    max_dim = round(x*0.20);

    uniform_int_distribution <int> U_CAIXAS(1,20);
    uniform_int_distribution <int> U_TIPOS_CAIXAS(0,(tipos_caixas-1));
    uniform_int_distribution <int> U_DIMENSOES(1,max_dim);
    //uniform_int_distribution <int> U_MASSA(massa_minima,massa_maxima);
    //uniform_int_distribution <int> U_MASSA(massa_minima,massa_maxima);

    vector<vector<int>> caixas;


    ofstream escritor(caminho_nome);
    escritor << tipos_caixas << " " << numero_pontos << "\n";
    escritor << x <<" " << y << " " << z << "\n";
    for(int i=0;i<tipos_caixas;i++)
    {
        vector<int> v;
        int x = U_DIMENSOES(r);
        int y = U_DIMENSOES(r);
        int z = U_DIMENSOES(r);
        v.push_back(x);v.push_back(y);v.push_back(z);
        caixas.push_back(v);
        escritor << x << " " << y << " " << z << " 0 99999 \n"; //massa = 0, carga máxima = 99999
    }
    for(int i=0;i<numero_pontos;i++)
    {
        int tipo_caixa = U_TIPOS_CAIXAS(r);
        int volume_caixa = (int)caixas[tipo_caixa][0]*(int)caixas[tipo_caixa][1]*(int)caixas[tipo_caixa][2];
        int numero_caixas = round(volume_por_ponto/volume_caixa);
        escritor << numero_caixas << " " << tipo_caixa << "\n";
    }
    escritor << "0";

    escritor.close();
}

void gera_instancia(int x, int y, int z, int tipos_caixas, string caminho_nome, int numero_pontos,int massa_minima,int massa_maxima,
                    int carga_minima, int carga_maxima)
{
    random_device r;
    int max_dim = 0;
    int volume_palete = (int)x*(int)y*(int)z;
    int volume_por_ponto = round(volume_palete/numero_pontos);
    max_dim = round(x*0.20);

    uniform_int_distribution <int> U_CAIXAS(1,20);
    uniform_int_distribution <int> U_TIPOS_CAIXAS(0,(tipos_caixas-1));
    uniform_int_distribution <int> U_DIMENSOES(1,max_dim);
    uniform_int_distribution <int> U_MASSA(massa_minima,massa_maxima);
    uniform_int_distribution <int> U_CARGA(carga_minima,carga_maxima);
    //uniform_int_distribution <int> U_MASSA(massa_minima,massa_maxima);

    vector<vector<int>> caixas;


    ofstream escritor(caminho_nome);
    escritor << tipos_caixas << " " << numero_pontos << "\n";
    escritor << x <<" " << y << " " << z << "\n";
    for(int i=0;i<tipos_caixas;i++)
    {
        vector<int> v;
        int x = U_DIMENSOES(r);
        int y = U_DIMENSOES(r);
        int z = U_DIMENSOES(r);
        v.push_back(x);v.push_back(y);v.push_back(z);
        caixas.push_back(v);

        int massa = U_MASSA(r);
        int carga = U_CARGA(r);
        escritor << x << " " << y << " " << z << " " << massa << " " << carga << "\n"; //massa = 0, carga máxima = 99999
    }
    for(int i=0;i<numero_pontos;i++)
    {
        int tipo_caixa = U_TIPOS_CAIXAS(r);
        int volume_caixa = (int)caixas[tipo_caixa][0]*(int)caixas[tipo_caixa][1]*(int)caixas[tipo_caixa][2];
        int numero_caixas = round(volume_por_ponto/volume_caixa);
        escritor << numero_caixas << " " << tipo_caixa << "\n";
    }
    escritor << "0";








    escritor.close();
}

void gera_instancia(int x, int y, int z, int tipos_caixas, string caminho_nome, int numero_pontos,int massa_minima,int massa_maxima,
                    int carga_minima, int carga_maxima, int min_caixas_restritas, int max_caixas_restritas, int min_restricoes_por_caixas,
                    int max_restricoes_caixa)
{

    random_device r;
    int max_dim = 0;
    int volume_palete = (int)x*(int)y*(int)z;
    int volume_por_ponto = round(volume_palete/numero_pontos);
    max_dim = round(x*0.20);

    uniform_int_distribution <int> U_CAIXAS(1,20);
    uniform_int_distribution <int> U_TIPOS_CAIXAS(0,(tipos_caixas-1));
    uniform_int_distribution <int> U_TIPOS_ROTACAO(0,5);
    uniform_int_distribution <int> U_DIMENSOES(1,max_dim);
    uniform_int_distribution <int> U_MASSA(massa_minima,massa_maxima);
    uniform_int_distribution <int> U_CARGA(carga_minima,carga_maxima);
    uniform_int_distribution <int> U_CAIXAS_RESTRITAS(min_caixas_restritas,max_caixas_restritas);
    uniform_int_distribution <int> U_NUMERO_RESTRICOES(min_restricoes_por_caixas,max_restricoes_caixa);

    //uniform_int_distribution <int> U_MASSA(massa_minima,massa_maxima);

    vector<vector<int>> caixas;


    ofstream escritor(caminho_nome);
    escritor << tipos_caixas << " " << numero_pontos << "\n";
    escritor << x <<" " << y << " " << z << "\n";
    for(int i=0;i<tipos_caixas;i++)
    {
        vector<int> v;
        int x = U_DIMENSOES(r);
        int y = U_DIMENSOES(r);
        int z = U_DIMENSOES(r);
        v.push_back(x);v.push_back(y);v.push_back(z);
        caixas.push_back(v);

        int massa = U_MASSA(r);
        int carga = U_CARGA(r);
        escritor << x << " " << y << " " << z << " " << massa << " " << carga << "\n"; //massa = 0, carga máxima = 99999
    }
    for(int i=0;i<numero_pontos;i++)
    {
        int tipo_caixa = U_TIPOS_CAIXAS(r);
        int volume_caixa = (int)caixas[tipo_caixa][0]*(int)caixas[tipo_caixa][1]*(int)caixas[tipo_caixa][2];
        int numero_caixas = round(volume_por_ponto/volume_caixa);
        escritor << numero_caixas << " " << tipo_caixa << "\n";
    }

    //restricoes de rotação das caixas
    int n_caixas_restritas = U_CAIXAS_RESTRITAS(r);
    escritor << n_caixas_restritas << "\n";

    vector<int> caixas_selecionadas, n_restricoes,tipos_rotacoes;
    while(caixas_selecionadas.size()<n_caixas_restritas)
    {
        int tipo_caixa = U_TIPOS_CAIXAS(r);
        if(find(caixas_selecionadas.begin(),caixas_selecionadas.end(),tipo_caixa) == caixas_selecionadas.end()){caixas_selecionadas.push_back(tipo_caixa);}
    }
    for(int i=0;i<caixas_selecionadas.size();i++)
    {
        int nn_restricoes = U_NUMERO_RESTRICOES(r);
        n_restricoes.push_back(nn_restricoes);
    }


    vector<vector<int>> t_rotacao;
    vector<int> v{0,0,0};
    for(int i=0;i<3;i++)
    {
        v[0] = i;;
        for(int j=0;j<3;j++)
        {
            v[1] = j;
            for(int k=0;k<3;k++)
            {
               v[2] = k;
               if(i != j && i != k && j != k)
               {
                   t_rotacao.push_back(v);
               }

            }
        }
    }

    for(int i = 0;i<caixas_selecionadas.size();i++)
    {
        escritor << caixas_selecionadas[i] << " " << n_restricoes[i] << " ";
        while(tipos_rotacoes.size()<n_restricoes[i])
        {
            int tipo_caixa = U_TIPOS_ROTACAO(r);
            if(find(tipos_rotacoes.begin(),tipos_rotacoes.end(),tipo_caixa) == tipos_rotacoes.end()){tipos_rotacoes.push_back(tipo_caixa);}
        }
        for(int k=0;k<tipos_rotacoes.size();k++)
        {
           escritor << t_rotacao[tipos_rotacoes[k]][0] << " " << t_rotacao[tipos_rotacoes[k]][1] << " " << t_rotacao[tipos_rotacoes[k]][2] << "\n";
        }
        tipos_rotacoes.clear();
    }


    escritor.close();
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_x_valueChanged(double arg1)
{
    this->ui->GLwidget->x = arg1;
}

void MainWindow::on_y_valueChanged(double arg1)
{

     this->ui->GLwidget->y = arg1;
}

void MainWindow::on_z_valueChanged(double arg1)
{
     this->ui->GLwidget->z = arg1;
}

void MainWindow::on_R_valueChanged(double arg1)
{
     this->ui->GLwidget->R = arg1;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
     this->ui->GLwidget->wired = checked;
}

void MainWindow::on_Resolver_clicked()
{
    for(int i=0;i<solucao.GetUpperBound(0);i++)
    {
             this->ui->GLwidget->sol[i].clear();
    }

    packing3D p(x_palete,y_palete,y_palete,caixas,h1);
    p.pack(tipo_caixas,qtde_caixas);
    matrix solucao = p.getSolucao();
    solucao.print();
    vector<double> indicadores;
    indicadores = p.getIndicadores();


    for(int i=0;i<solucao.GetUpperBound(0);i++)
    {
        vector<float> v;
        for(int j=0;j<solucao.GetUpperBound(1);j++)
        {
            v.push_back((float)solucao[i][j]);
        }
        this->ui->GLwidget->sol.push_back(v);
    }

    this->ui->GLwidget->resolvido = true;
}

void MainWindow::on_LerDados_clicked()
{
    //pegando o caminho do arquivo
     QString filename = QFileDialog::getOpenFileName(
             this, tr("BUsca de arquivos"),"/home/alexandre/Documentos/Programas_c++/carga_3d/caixas","All files (*.*)");
     QMessageBox::information(this,tr("Nome do arquivo"),filename);
     std::string utf8_text = filename.toUtf8().constData();
     vector<string> nomes;
     nomes.push_back(utf8_text);
     x_palete = y_palete = z_palete = 0;
     ler_dados(x_palete,y_palete,z_palete,caixas,tipo_caixas,qtde_caixas,nomes[0],h1);
     this->ui->GLwidget->x_palete = (float)x_palete;
     this->ui->GLwidget->y_palete = (float)y_palete;
     this->ui->GLwidget->z_palete = (float)z_palete;
     //////
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    this->ui->GLwidget->angulo = arg1;
}

void MainWindow::on_R1_valueChanged(double arg1)
{
     this->ui->GLwidget->a1 = arg1;
}

void MainWindow::on_R2_valueChanged(double arg1)
{
      this->ui->GLwidget->a2 = arg1;
}

void MainWindow::on_R3_valueChanged(double arg1)
{
      this->ui->GLwidget->a3 = arg1;
}

void MainWindow::on_animacao_clicked(bool checked)
{
    this->ui->GLwidget->animacao = checked;
}

void MainWindow::on_animacao_clicked()
{

}

void MainWindow::on_Eixos_clicked()
{

}

void MainWindow::on_Eixos_clicked(bool checked)
{
     this->ui->GLwidget->eixos = checked;
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
     this->ui->GLwidget->palete = checked;
}
