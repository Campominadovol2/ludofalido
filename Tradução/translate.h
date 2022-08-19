#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <iostream>
#include <locale.h>
#include <fstream>
#include <cstring>
using namespace std;

#define width 200
#define height 3

void gravamentos(char basetext[][], int lin, int col)
{
    setlocale(LC_ALL, "portuguese");
    ifstream entrada;
    ofstream saida;
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

    return;
}

void traduzimentos(char basetext[])
{
    setlocale(LC_ALL, "portuguese");
    FILE *apontador;
    apontador = fopen("base.txt", "r");

    // trecho para verificar se o arquivo especificado existe
    if (apontador == NULL)
    {
        printf("Arquivo não encontrado");
        getchar();
        exit(0);
    }

    char frase[100]; // vetor de caracteres para armazenar as palavras
    while (fgets(frase, 100, apontador) != NULL)
    {
        printf("%s", frase);
    }

    fclose(apontador);
}

#endif // TRANSLATE_H