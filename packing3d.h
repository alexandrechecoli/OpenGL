#ifndef PACKING3D_H
#define PACKING3D_H
#include <matrix.h>
#include <vector>
#include <map>

class packing3D
{

private:


    class espaco{
    public:

        int x = -1;
        int y = -1;
        int z = -1;
        int X = -1;
        int Y = -1;
        int Z = -1;

        void reset()
        {
            x = -1;
            y = -1;
            z = -1;
            X = -1;
            Y = -1;
            Z = -1;
        }

    };

    class no
    {
    public:
        bool aberto = true;
        espaco e_vazio;
        espaco e_caixa;
        vector<int> filhos{-1,-1,-1}; //possivel gerar 3 filhos, se não forem gerados, valores permanecem (-1)
        int pai = 0;
        int numero_espaco; // de qual espaço a caixa foi inserida;
        int massa_acumulada = 0;
        int tipo_caixa = -1;
        //int filhos[3] = {-1,-1,-1};
        //(Xe,Ye,Ze) -> dimensões do espaço
        //(xe,ye,ze) -> ponto inferior esquerdo do espaço
        //(xc,yc,zc) -> ponto inferior esquerdo da caixa que está no espaço
    };

    vector<no> arvore;
    map <int, vector<vector<int>>> r_caixas;

public:

    packing3D(int _x_pal, int _y_pal, int _z_pal, matrix &tipos_caixas,map <int, vector<vector<int>>> _r_caixas);
    void pack(vector<int> &_v_caixas, vector<int> &_qtde_caixas);
    int getNumeroCaixasEmpacotadas();
    matrix getSolucao();
    vector<vector<int> > getSolucaoV();
    void ler_dados();
    vector<double> getIndicadores();

private:
    int x_pal;
    int y_pal;
    int z_pal;
    int vol_pal;

    double volume_total_caixas = 0;
    double total_caixas = 0;
    int apontador = 0; //apontador para a caixa a ser inserida no momento

    matrix caixas;
    vector<int> v_caixas;
    vector<int> qtde_caixas;
    vector<vector<int>> tipos_rotacao;
    void expande(no pai);
    void gera_e1(no &pai,espaco &e1);
    void gera_e2(no &pai,espaco &e2);
    void gera_e3(no &pai,espaco &e3);
    void atualiza_apontador();//atualiza o apontador de caixas e os vetores v_caixas e qtde_caixas
    void expande_no(int &numero_pai, int tipo_caixa);
    void insere_caixa(espaco &caixa, espaco &obj, int &tipo_caixa);
    bool verifica_factibilidade_rotacao(espaco &obj,espaco &caixa);
    double getAproveitamentoNumeroCaixas(); // total de caixas empacotadas/ total de caixas a serem empacotadas
    double getAproveitamentoVolumeCaixas(); //volume total de caixas empacotadas/ volume total de caixas
    double getAproveitamentoPalete();
    double getNumeroCaixasTotal();
    bool verifica_factibilidade_massa(int tipo_caixa, int no_pai, int n_espaco_no);
    void atualiza_massa(int tipo_caixa,int no_pai, int n_espaco_no);

};

#endif // PACKING3D_H
