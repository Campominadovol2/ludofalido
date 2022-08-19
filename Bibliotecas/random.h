#ifndef RANDOM_H
#define RANDOM_H
#include <time.h>
#include "gconio.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "desenhos.h"
using namespace std;

// FAZ SORTEIO DE NUMEROS
void random_numbers(int vetor[], int tam)
{
    //srand(time(NULL));
    for (int i = 0; i < tam; i++)
    {
        do
        {
            vetor[i] = rand() % 7;
        } while (vetor[i] == 0 || vetor[i] > 7);

        if (vetor[i] != 6)
        {
            break;
        }
    }
}

// ZERA TODOS OS ELEMENTOS DO VETOR, EVITA LIXO DE MEMORIA
void zerarvetor(int vetor[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        vetor[i] = 0;
    }
}

// RETIRA OS ZEROS, ORDENA DE FORMA DECRESCENTE E RETORNA A QUANTIDADE DE ELEMENTOS
void organizador(int vetor[])
{
    int aux[10] = {0};

    // serve para retirar as primeiras casas com 0 e contar os numeros que ainda restam no vetor
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        // copiara os valores diferentes de 0 para o vetor auxiliar
        if (vetor[i] != 0)
        {
            aux[j] = vetor[i];
            j++;
        }
    }

    // copiara os valores do auxiliar organizado para o vetor original
    for (int i = 0; i < 10; i++)
    {
        vetor[i] = aux[i];
    }

    // colocara os numeros em ordem decrescente
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            int temp = 0;
            if (vetor[i] < vetor[j])
            {
                temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }

    // contara o numero de elementos (diferentes de 0)
    int ind = 0;
    while (vetor[ind] != 0)
    {
        ind++;
    }
    // return ind;
}

// FAZ OS NOVOS SORTEIOS, CONCATENA. USAR O RETURN PARA QUEBRAR O LAÇO
void deletetoken(int vetor[])
{
    int aux[7] = {0};
    organizador(vetor);
    random_numbers(aux, 7);
    // numeros a partir da quarta posicao serao zerados para evitar lixo de memoria
    for (int i = 3; i < 10; i++)
    {
        vetor[i] = 0;
    }

    // concatenara o vetor principal e auxiliar
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        if (vetor[i] == 0)
        {
            if (aux[j] != 0)
            {
                vetor[i] = aux[j];
                j++;
            }
            else
            {
                break;
            }
        }
    }

    // ordenacao em ordem decrescente
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            int temp = 0;
            if (vetor[i] < vetor[j])
            {
                temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
    organizador(vetor);
}

// EXIBE ELEMENTOS DO VETOR
void viewvector(int vetor[], int tam, int posx, int posy)
{

    gotoxy(posx, posy);
    int i = 0;
    while (vetor[i] != 0)
    {
        printf("[%i]", vetor[i]);
        i++;
    }
}

// OBTEM O NUMERO DE ELEMENTOS GERAIS E OS DE NUMERO SEIS
void countnumbers(int vetor[], int &allnumbers, int &allnumberssix)
{
    organizador(vetor);
    allnumbers = 0;
    allnumberssix = 0;
    int i = 0;
    while (vetor[i] > 0 && vetor[i] < 7)
    {
        // fará uma varredura pelo vetor recem preenchido pelo sorteio
        if (vetor[i] == 6)
        {
            // contara o numero de "6", ja que eh um numero especial para o jogo
            allnumberssix++;
        }
        // contara o numero geral de elementos
        allnumbers++;
        i++;
    }
}

// NECESSARIO PARA IR EXCLUINDO OS ELEMENTOS DE NUMERO 6
void removesix(int vetor[], int &numberssix, int &allnumbers)
{
    for (int i = 0; i < 10; i++)
    {
        if (vetor[i] == 6)
        {
            // subtrai algum elemento de numero "6"
            vetor[i] = 0;
            numberssix--;
            break;
        }
    }
    allnumbers--;
}

// NECESSARIO PARA IR EXCLUINDO OS ELEMENTOS JA USADOS
void clearposic(int vetor[], int &allnumbers)
{
    for (int i = 0; i < 10; i++)
    {
        if (vetor[i] != 0)
        {
            // movimenta a peca
            vetor[i] = 0;
            allnumbers--;
            return;
        }
    }
}

// CONDICIONAL PARA O CICLO DE JOGADAS
void remaining(int vetor[], int &pass)
// ira checar se ainda existe algum elemento no vetor, tem uma condicao especial para quebrar o while em caso de vencedor]
// 1 - se ainda tiver elementos, 0 - se nao tiver elemenros
{
    for (int i = 0; i < 10; i++)
    {
        if (vetor[i] != 0)
        {
            pass = 1;
            return;
        }
    }
    pass = 0;
}

#endif // RANDOM_H