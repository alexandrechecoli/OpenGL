#ifndef MAR_H
#define MAR_H
#include <string>
#include <dirent.h>
#include <vector>
#include <string>

//multiple archive reader (MAR)
//esta classe tem por objetivo ler todos os arquivos de um diretorio, e armazenar em um vetor de string.
//getArchiveName -> retorna um vetor de strings com todos os nomes de arquivos de uma pasta.
//getArchivePath -> retorna um vetor de strings com todos os caminhos dos arquivos de uma pasta.
class MAR
{
public:

    MAR(const char* path);
    std::vector<std::string>  getArchiveName();
    std::vector<std::string>  getArchivePath();
    void PrintNames();
    void PrintPaths();

private:

    std::vector<std::string> nomes;
    std::vector<std::string> caminhos;

};

#endif // MAR_H
