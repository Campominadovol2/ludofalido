#ifndef ANALISE__H
#define ANALISE__H

#include "desenhos.h"

int *sortearDados(size_t &size)
{
    size = 1;
    int i = 0;
    int *vetor = (int *)malloc(sizeof(int));

    vetor[i] = rand() % 6 + 1;

    while (vetor[i++] == 6 && size <= 2)
    {
        size++;
        vetor = (int *)realloc(vetor, sizeof(int) * size);
        vetor[i] = rand() % 6 + 1;
    }

    return vetor;
}

int contarNum6(int *vetor, size_t size)
{
    int r = 0;
    for (int i = 0; i < size; i++)
    {
        if (vetor[i] == 6)
        {
            r++;
        }
    }

    return r;
}

bool ehPossivelJogar(Player p, int dado)
{

    for (int i = 0; i < 4; i++)
    {
        if (p.piece[i].letra != ' ' && !p.piece[i].estaNaPosicaoInicial && p.piece[i].coordenada < 52)
            return true;
    }

    for (int i = 0; i < 4; i++)
    {
        if (p.piece[i].letra != ' ')
            if (p.piece[i].coordenada + dado <= p.piece[i].coordenadaFinal)
                return true;
    }

    if (dado == 6)
    {
        for (int i = 0; i < 4; i++)
        {
            if (p.piece[i].letra != ' ' && p.piece[i].estaNaPosicaoInicial)
                return true;
        }
    }

    return false;
}

int tokensDisponiveis(Player p, int _pos_x, int __pos_y, char vetor[], bool cond)
{
    int r = 0;
    for (int i = 0; i < 4; i++)
    {
        if (p.piece[i].letra != ' ')
        {
            if (cond)
            {
                gotoxy(_pos_x, __pos_y++);
                cout << "[" << p.piece[i].letra << "]";
                vetor[r] = p.piece[i].letra;
                r++;
            }
            else
            {
                if (!p.piece[i].estaNaPosicaoInicial)
                {
                    gotoxy(_pos_x, __pos_y++);
                    cout << "[" << p.piece[i].letra << "]";
                    vetor[r] = p.piece[i].letra;
                    r++;
                }
            }
        }
    }

    return r;
}
char selecionartoken(Player p, bool cond)
{
    char tokensdisp[4];
    int quantidade = tokensDisponiveis(p, 40, 9, tokensdisp, cond);
    int numescolha = selecionar_opcao(37, 9, quantidade);

    return tokensdisp[numescolha - 1];
}

void viewvector(int vetor[], int tam, int posx, int posy)
{
    gotoxy(posx, posy);
    for (int i = 0; i < 10; i++)
    {
        printf("   ");
    }
    int i = 0;
    gotoxy(posx, posy);
    for (int i = 0; i < tam; i++)
    {
        if (vetor[i] != 0)
            printf("[%i]", vetor[i]);
    }
}

void bubble_n_sort(int *vetor, int tam, int startFromIndex)
{
    // ordenacao em ordem decrescente
    for (int i = startFromIndex; i < tam; i++)
    {
        for (int j = i + 1; j < tam; j++)
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
}

bool containSix(int *vetor, int tam)
{
    for (int i = 0; i < tam; i++)
        if (vetor[i] == 6)
            return true;

    return false;
}

int selecionarNumero(int *vetor, int size, char l, Player p)
{
    int x = 40, y = 10;
    int *arr = (int *)malloc(sizeof(int) * size);
    int k = 0;
    int pos = posicaoPeca(p, l);
    int temp2 = p.piece[pos].coordenadaFinal - p.piece[pos].coordenada;

    if (p.piece[posicaoPeca(p, l)].estaNaPosicaoInicial)
    {
        for (int i = 0; i < size; i++)
        {
            if (vetor[i] == 6)
            {
                gotoxy(x, y++);
                printf("[%d]", vetor[i]);
                arr[k] = 6;
                k++;
            }
        }

        int temp = selecionar_opcao(39, 10, k);
        return arr[k];
    }

    else if (temp2 <= 6 && temp2 >= 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (vetor[i] <= temp2 && vetor[i] != 0)
            {
                gotoxy(x, y++);
                printf("[%d]", vetor[i]);
                arr[k] = vetor[i];
                k++;
            }
        }

        int temp = selecionar_opcao(39, 10, k);
        return arr[k];
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (vetor[i] != 0)
            {
                gotoxy(x, y++);
                printf("[%d]", vetor[i]);
                arr[k] = vetor[i];
                k++;
            }
        }

        int temp = selecionar_opcao(39, 10, k);
        return arr[k];
    }
}
#endif