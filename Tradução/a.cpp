#include <locale.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
using std::cout;
using std::ifstream;
using std::ofstream;
#define lin 5
#define col 30
int main()
{
    setlocale(LC_ALL, "portuguese");
    ifstream entrada;
    ofstream saida;
    char basetext[lin][col];
    entrada.open("story.txt");
    if (entrada.fail())
    {
        cout << "A abertura do arquivo de entrada falhou.\n";
        exit(1);
    }
    for (int i = 0; i < lin; i++)
    {
        strcpy(basetext[i], " ");
    }

    char next;
    int linha = 0, coluna = 0;
    entrada.get(next);
    while (!entrada.eof())
    {

        if (next == '\n')
        {
            basetext[linha][coluna] = '\0';
            linha++;
            coluna = 0;
        }
        else
        {
            basetext[linha][coluna] = next;
            coluna++;
        }
        entrada.get(next);
    }
    entrada.close();

    printf("%s\n", basetext[3]);

    return 0;
}
