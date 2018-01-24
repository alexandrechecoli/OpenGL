#include "matrix.h"

matrix::matrix()
{

}

matrix::matrix(int _m, int _n)
{
   m = _m;
   n = _n;
   M = new int*[_m];
  for(int i=0;i<m;i++)
  {
    M[i] = new int[_n];
  }

  for(int i=0;i<m;i++)
  {
    for(int j=0;j<n;j++)
    {
      M[i][j] = 0;
    }
  }
}

void matrix::redim(int _m, int _n)
{
    m = _m;
    n = _n;
    M = new int*[_m];
   for(int i=0;i<m;i++)
   {
     M[i] = new int[_n];
   }

   for(int i=0;i<m;i++)
   {
     for(int j=0;j<n;j++)
     {
       M[i][j] = 0;
     }
   }
 }

matrix::~matrix() //destructor
{
  for(int i=0;i<m;i++)
  {
    delete[] M[i];
  }
  delete M;
  //cout << "matriz destruida \n";
}

void matrix::print() //prints the Matrix
{
      for(int i=0;i<m;i++)
      {
        for(int j=0;j<n;j++)
        {
          cout << M[i][j] << " ";
        }
      cout << "\n";
      }
      cout << "\n";
}

int matrix::GetUpperBound(int dim)
{
  if(dim==0){ return m;
  } else{return n;};

}

int matrix::max() //Calculates the maximum of the Matrix
{
  double max = -numeric_limits<double>::max();
  for(int i=0;i<m;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(M[i][j]>max)
      {
        max = M[i][j];
      }
    }
  }
  return max;
}

int matrix::min() //Calculates the minimum of the Matrix
{
  double max = numeric_limits<double>::max();
  for(int i=0;i<m;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(M[i][j]<max)
      {
        max = M[i][j];
      }
    }
  }
  return max;

}

int* & matrix::operator [](const int &index) const  // overloading operator []
{
  return  M[index];
}









