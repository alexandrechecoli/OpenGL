#include "mar.h"
#include <string>
#include <iostream>

MAR::MAR(const char* path)
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (path)) != NULL) {

      /* imprime todos os arquivas no diretorio */
      while ((ent = readdir (dir)) != NULL) {
          nomes.push_back(ent->d_name);
          std::string concat = "";
          std::string espaco = "/";
          concat = path;
          concat = path +  espaco + nomes[nomes.size()-1];
          if(concat[concat.size()-3] == 't' && concat[concat.size()-2] == 'x' && concat[concat.size()-1] == 't')
          {
              caminhos.push_back(concat);
          }


          //cout << ent->d_name << "\n";
      }
      closedir (dir);
    } else {
      /* diretorio inexistente */
      perror ("");
      //return EXIT_FAILURE;
    }

}

std::vector<std::string> MAR::getArchivePath()
{
 return caminhos;
}

std::vector<std::string> MAR::getArchiveName()
{
 return nomes;
}

void MAR::PrintNames()
{
    for(int i=0;i<caminhos.size();i++)
    {
        std::cout << nomes[i] << "\n";
    }
}

void MAR::PrintPaths()
{
    for(int i=0;i<caminhos.size();i++)
    {
        std::cout << caminhos[i] << "\n";
    }
}
