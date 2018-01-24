#include "packing3d.h"

packing3D::packing3D(int _x_pal, int _y_pal, int _z_pal, matrix &tipos_caixas, map<int, vector<vector<int> > > _r_caixas)
{
     x_pal = _x_pal;
     y_pal = _y_pal;
     z_pal = _z_pal;
     vol_pal = (int)x_pal*(int)y_pal*(int)z_pal;

     caixas.redim(tipos_caixas.GetUpperBound(0),tipos_caixas.GetUpperBound(1));
     for(int i=0;i < tipos_caixas.GetUpperBound(0);i++)
     {
         for(int j=0;j<tipos_caixas.GetUpperBound(1);j++)
         {
             caixas[i][j] = tipos_caixas[i][j];
         }
     }
     r_caixas = _r_caixas;


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
                    tipos_rotacao.push_back(v);
                }

             }
         }
     }



     //caixas.print();
}

void packing3D::pack(vector<int> &_v_caixas, vector<int> &_qtde_caixas)
{
    qtde_caixas.clear();
    v_caixas.clear();
    total_caixas = 0;
    volume_total_caixas = 0;
    for(int i=0;i<_v_caixas.size();i++)
    {
        total_caixas += _qtde_caixas[i];
        volume_total_caixas += caixas[_v_caixas[i]][3]*_qtde_caixas[i];
        qtde_caixas.push_back(_qtde_caixas[i]);
        v_caixas.push_back(_v_caixas[i]);
    }


    no raiz;
    espaco palete,caixa;

    palete.x = palete.y = palete.z = caixa.x = caixa.y = caixa.z = 0;
    palete.X = x_pal ; palete.Y = y_pal ; palete.Z = z_pal;
    caixa.X = caixas[v_caixas[apontador]][0] ; caixa.Y = caixas[v_caixas[apontador]][1] ; caixa.Z = caixas[v_caixas[apontador]][2];
    raiz.e_caixa = caixa;
    raiz.e_vazio = palete;
    raiz.pai = -1;
    raiz.tipo_caixa = v_caixas[apontador];
    arvore.push_back(raiz);

    int numero_raiz = 0;
    expande_no(numero_raiz,v_caixas[apontador]);

}

void packing3D::atualiza_apontador()
{
    if(qtde_caixas[apontador] != 0)
    {
        qtde_caixas[apontador]--;        
        if(qtde_caixas[apontador] == 0)
        {
            if(apontador != v_caixas.size()-1)
            {
                apontador++;
            }
        }
    }
    else{apontador++;}
}

void packing3D::expande_no(int &numero_pai, int tipo_caixa)
{
    //Como esta função será recursiva, qualquer variavel que seja declarada aqui, fica presa no pop, por esse
    //motivo, todas as variaveis usadas são as globais da arvore

    arvore[numero_pai].aberto = false;
    atualiza_apontador();

   espaco e;
   gera_e1(arvore[numero_pai],e);
    if(e.x!=-1)
    {
        no f1;
        f1.e_vazio = e;        
        arvore[numero_pai].filhos[0] = arvore.size();
        arvore.push_back(f1);
    }
    e.reset();

    gera_e2(arvore[numero_pai],e);
    if(e.x!=-1)
    {
        no f2;
        f2.e_vazio = e;
        arvore[numero_pai].filhos[1] = arvore.size();//arvore.size();
        arvore.push_back(f2);
    }
        e.reset();

    gera_e3(arvore[numero_pai],e);
    if(e.x!=-1) {
        no f3;
        f3.e_vazio = e;
        arvore[numero_pai].filhos[2] = arvore.size();
        arvore.push_back(f3);
    }
    e.reset();

    /*Nessa parte pode ter uma variação, criar um criterio de utilização dos espações, talvez um vetor com 3 posições,
em que cada posição aponta para uma função que expande um determinado espaço*/
    /////////////////////////////////////////////////////////////////////////
    //expandindo espaço 2
    if(apontador == (v_caixas.size()-1) && qtde_caixas[apontador] == 0) return;
    if(arvore[numero_pai].filhos[1] != -1)
    {
        insere_caixa(e,arvore[arvore[numero_pai].filhos[1]].e_vazio,v_caixas[apontador]);
        if(e.x != -1)
        {
            if(verifica_factibilidade_massa(v_caixas[apontador],numero_pai,1))
            {
                atualiza_massa(v_caixas[apontador],numero_pai,1);
                arvore[arvore[numero_pai].filhos[1]].tipo_caixa = v_caixas[apontador];
                arvore[arvore[numero_pai].filhos[1]].numero_espaco = 1;
                arvore[arvore[numero_pai].filhos[1]].e_caixa = e;
                arvore[arvore[numero_pai].filhos[1]].pai = numero_pai;
                expande_no(arvore[numero_pai].filhos[1],v_caixas[apontador]);
            }

        }
        e.reset();
    }

    if(apontador == (v_caixas.size()-1) && qtde_caixas[apontador] == 0) return;
    if((arvore[numero_pai].filhos[2] != -1)/*existe o espaço 3?*/)
    {
        insere_caixa(e,arvore[arvore[numero_pai].filhos[2]].e_vazio,v_caixas[apontador]); //Define as dimensões da caixa "e" para que ela caiba no espaço
    //se as dimensões do espaço voltarem -1, quer dizer que a caixa e não cabe no espaço
        if(e.x != -1)
        {
            if(verifica_factibilidade_massa(v_caixas[apontador],numero_pai,2))
            {
                atualiza_massa(v_caixas[apontador],numero_pai,2);
                arvore[arvore[numero_pai].filhos[2]].tipo_caixa = v_caixas[apontador];
                arvore[arvore[numero_pai].filhos[2]].numero_espaco = 2;
                arvore[arvore[numero_pai].filhos[2]].e_caixa = e;
                arvore[arvore[numero_pai].filhos[2  ]].pai = numero_pai;
                expande_no(arvore[numero_pai].filhos[2],v_caixas[apontador]);
            }

        }
        e.reset();
    }

    //expandindo espaço 1


    //expandindo espaço 0
    if(apontador == (v_caixas.size()-1) && qtde_caixas[apontador] == 0) return;
    if(arvore[numero_pai].filhos[0] != -1)
    {
        insere_caixa(e,arvore[arvore[numero_pai].filhos[0]].e_vazio,v_caixas[apontador]);
        if(e.x != -1)
        {
            if(verifica_factibilidade_massa(v_caixas[apontador],numero_pai,0))
            {
                atualiza_massa(v_caixas[apontador],numero_pai,0);
                arvore[arvore[numero_pai].filhos[0]].tipo_caixa = v_caixas[apontador];
                arvore[arvore[numero_pai].filhos[0]].numero_espaco = 0;
                arvore[arvore[numero_pai].filhos[0]].e_caixa = e;
                arvore[arvore[numero_pai].filhos[0]].pai = numero_pai;
                expande_no(arvore[numero_pai].filhos[0],v_caixas[apontador]);
            }
        }
        e.reset();
    }

    /////////////////////////////////////////////////////////////////////////
}

bool packing3D::verifica_factibilidade_massa(int tipo_caixa,int no_pai, int n_espaco_no)
{   
    if(n_espaco_no == 2)
    {
        int massa_acumulada = arvore[no_pai].massa_acumulada + caixas[tipo_caixa][4];
        if(massa_acumulada > caixas[arvore[no_pai].tipo_caixa][5]) return false;
    }

    int no_atual = no_pai;
    while(no_atual != 0 )
    {

        if(arvore[no_atual].numero_espaco == 2)
        {
            int massa_acumulada = arvore[arvore[no_atual].pai].massa_acumulada + caixas[tipo_caixa][4];
            if(massa_acumulada > caixas[arvore[arvore[no_atual].pai].tipo_caixa][5])
            {
                return false;
            }
        }
        no_atual = arvore[no_atual].pai;

    }
    return true;
}

void packing3D::atualiza_massa(int tipo_caixa,int no_pai, int n_espaco_no)
{
    if(n_espaco_no == 2)
    {
        arvore[no_pai].massa_acumulada = arvore[no_pai].massa_acumulada + caixas[tipo_caixa][4];
    }

    int no_atual = no_pai;
    while(no_atual != 0 )
    {
        if(arvore[no_atual].numero_espaco == 2)
        {
            arvore[arvore[no_atual].pai].massa_acumulada += caixas[tipo_caixa][4];
        }
        no_atual = arvore[no_atual].pai;
    }
}

void packing3D::insere_caixa(espaco &caixa,espaco &obj, int &tipo_caixa)
{

    caixa.x = (int)obj.x; caixa.y = obj.y;caixa.z = obj.z;
    /*gerar as combinações de rotações e verificar a factibilidade em algum ponto
    Criar um criterio para escolher qual posição de caixa será utilizada, talvez
    verificar a factibilidade de todas, e das quais forem factiveis, selecionar segundo algum criterio*/
    ////////////////////////////////////////////////////////////////////////

    map <int, vector<vector<int>> >::iterator k;
    k = r_caixas.find(tipo_caixa);
    vector<int> melhor_combinacao{-1,-1,-1};
    double menor_perda = 0;//x_pal*y_pal;

    if(k != r_caixas.end())
    {
        for(int i=0;i<tipos_rotacao.size();i++) //para todos as possibilidades de rotação da caixa
        {
            bool fact = true;
            for(int j=0;j<k->second.size();j++)
            {
                if(tipos_rotacao[i] == k->second[j]){fact = false; break;}
            }
            if(fact == true)
            {
                caixa.X = (int)caixas[tipo_caixa][tipos_rotacao[i][0]];caixa.Y = (int)caixas[tipo_caixa][tipos_rotacao[i][1]];caixa.Z = (int)caixas[tipo_caixa][tipos_rotacao[i][2]];
                if(verifica_factibilidade_rotacao(obj,caixa))return;
            }
        }

    }else{

        for(int i=0;i<tipos_rotacao.size();i++) //para todos as possibilidades de rotação da caixa
        {

                caixa.X = (int)caixas[tipo_caixa][tipos_rotacao[i][0]];
                caixa.Y = (int)caixas[tipo_caixa][tipos_rotacao[i][1]];
                caixa.Z = (int)caixas[tipo_caixa][tipos_rotacao[i][2]];
                if(verifica_factibilidade_rotacao(obj,caixa))
                {
                    return;
                    double area = ((double)caixa.X)*((double)caixa.Y);
                    double perda_atual = area/((double)obj.X*(double)obj.Y);
                    if(perda_atual > menor_perda)
                    {
                            menor_perda = perda_atual;
                            melhor_combinacao[0] = tipos_rotacao[i][0];
                            melhor_combinacao[1] = tipos_rotacao[i][1];
                            melhor_combinacao[2] = tipos_rotacao[i][2];
                    }

                }
        }

        if(melhor_combinacao[0]!=-1)
        {
            caixa.X = (int)caixas[tipo_caixa][melhor_combinacao[0]];
            caixa.Y = (int)caixas[tipo_caixa][melhor_combinacao[1]];
            caixa.Z = (int)caixas[tipo_caixa][melhor_combinacao[2]];
        }else{caixa.reset();}
    }


    ////////////////////////////////////////////////////////////////////////
}

void packing3D::gera_e1(no &pai, espaco &e)
{
    int X = ((int)pai.e_vazio.X - (int)pai.e_caixa.X);
    if(X > 0)
    {
        e.x = (int)pai.e_caixa.x + (int)pai.e_caixa.X;
        e.y = (int)pai.e_caixa.y;
        e.z = (int)pai.e_caixa.z;

        e.X = X;
        e.Y = pai.e_vazio.Y;
        e.Z = pai.e_vazio.Z;
    }
}

void packing3D::gera_e2(no &pai, espaco &e)
{
    int Y = ((int)pai.e_vazio.Y - (int)pai.e_caixa.Y);
    if(Y > 0)
    {
        e.x = (int)pai.e_caixa.x;
        e.y = (int)pai.e_caixa.y + (int)pai.e_caixa.Y;
        e.z = (int)pai.e_caixa.z;

        e.X = (int)pai.e_caixa.X;
        e.Y = Y;
        e.Z = (int)(pai).e_vazio.Z;
    }

}

void packing3D::gera_e3(no &pai, espaco &e)
{
    int Z = ((int)pai.e_vazio.Z - (int)pai.e_caixa.Z);
    if(Z > 0)
    {
        e.x = (int)pai.e_caixa.x;
        e.y = (int)pai.e_caixa.y;
        e.z = (int)pai.e_caixa.z + (int)pai.e_caixa.Z;

        e.X = (int)pai.e_caixa.X;
        e.Y = (int)pai.e_caixa.Y;
        e.Z = Z;
    }

}

/*dado um ponto inicial (no obj) e as dimensões (X,Y,X) da caixa, verifica se a mesma cabe no
objeto*/
bool packing3D::verifica_factibilidade_rotacao(espaco &obj,espaco &caixa)
{
    if((caixa.x-obj.x)+caixa.X <= obj.X)
    {
        if((caixa.y-obj.y)+caixa.Y <= obj.Y)
        {
            if((caixa.z-obj.z)+caixa.Z <= obj.Z)
            {
                return true;
            }
        }
    }
return false;
}

int packing3D::getNumeroCaixasEmpacotadas()
{
    int caixas_empacotadas = 0;
    for(int i=0; i< arvore.size();i++)
    {
        if((int)arvore[i].e_caixa.x != -1) caixas_empacotadas+=1;
    }
    return caixas_empacotadas;
}

vector<vector<int>> packing3D::getSolucaoV()
{
    vector<vector<int>> sol;
    for(int i=0;i<arvore.size();i++)
    {

        vector<int> v;
        if(arvore[i].e_caixa.x !=-1)
        {
            v.push_back(arvore[i].e_caixa.x);
            v.push_back(arvore[i].e_caixa.y);
            v.push_back((int)arvore[i].e_caixa.z);
            v.push_back(arvore[i].e_caixa.X);
            v.push_back(arvore[i].e_caixa.Y);
            v.push_back(arvore[i].e_caixa.Z);
            sol.push_back(v);
        }
    }

    return sol;
}

matrix packing3D::getSolucao()
{
    vector<vector<int>> sol;
    for(int i=0;i<arvore.size();i++)
    {

        vector<int> v;
        if(arvore[i].e_caixa.x !=-1)
        {
            v.push_back(arvore[i].e_caixa.x);
            v.push_back(arvore[i].e_caixa.y);
            v.push_back((int)arvore[i].e_caixa.z);
            v.push_back(arvore[i].e_caixa.X);
            v.push_back(arvore[i].e_caixa.Y);
            v.push_back(arvore[i].e_caixa.Z);
            sol.push_back(v);
        }
    }
        matrix c(sol.size(),6);

        for(int i=0;i<sol.size();i++)
        {
            c[i][0] = sol[i][0];
            c[i][1] = sol[i][1];
            c[i][2] = sol[i][2];
            c[i][3] = sol[i][3];
            c[i][4] = sol[i][4];
            c[i][5] = sol[i][5];
        }
    return c;
}

double packing3D::getAproveitamentoNumeroCaixas()
{
    double caixas_empacotadas = getNumeroCaixasEmpacotadas();
    return (double)caixas_empacotadas/(double)total_caixas;
}

double packing3D::getAproveitamentoVolumeCaixas()
{
    int vol_caixas_empacotadas = 0;

    for(int i=0;i<arvore.size();i++)
    {
        if(arvore[i].e_caixa.x != -1)
        {
            vol_caixas_empacotadas += (int)arvore[i].e_caixa.X*(int)arvore[i].e_caixa.Y*(int)arvore[i].e_caixa.Z;
        }
    }

    double aproveitamento_volume_caixas = (double)vol_caixas_empacotadas/(double)volume_total_caixas;

    return aproveitamento_volume_caixas;
}

double packing3D::getAproveitamentoPalete()
{

    int vol_caixas_empacotadas = 0;
    for(int i=0;i<arvore.size();i++)
    {
        if(arvore[i].e_caixa.x != -1)
        {
            vol_caixas_empacotadas += (int)arvore[i].e_caixa.X*(int)arvore[i].e_caixa.Y*(int)arvore[i].e_caixa.Z;
        }
    }

    double v = ((double)vol_caixas_empacotadas)/((double)vol_pal);



    return v;
}

vector<double> packing3D::getIndicadores()
{
    double AproveitamentoVolumePalete,AproveitamentoNumeroCaixas,AproveitamentoVolumeCaixas;
    AproveitamentoVolumePalete = getAproveitamentoPalete();
    AproveitamentoNumeroCaixas = getAproveitamentoNumeroCaixas();
    AproveitamentoVolumeCaixas = getAproveitamentoVolumeCaixas();

    vector<double> indicadores;
    indicadores.push_back(AproveitamentoVolumePalete);
    indicadores.push_back(AproveitamentoVolumeCaixas);
    indicadores.push_back(AproveitamentoNumeroCaixas);
    indicadores.push_back(getNumeroCaixasTotal());
    indicadores.push_back(getNumeroCaixasEmpacotadas());
    indicadores.push_back((volume_total_caixas/vol_pal));
    return indicadores;

}

double packing3D::getNumeroCaixasTotal()
{
    return total_caixas;
}






