#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <limits>

using namespace std;

class matrix
{
public:

    matrix();
    matrix(int,int);
    ~matrix();//destrutor
    void print(); //imprime a matriz
    void redim(int _m, int _n); //inicializa a matriz, quando nao foi feito no construtor
    int* & operator[](const int &index) const;
    int GetUpperBound(int dim);
    int max();
    int min();

public:
   int** M;
private:
    int m;
    int n;
};

#endif // MATRIX_H
