#include <iostream>
#include "./Bibliotecas/gconio.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <time.h>
#ifdef __WIN32
#include <windows.h>
#endif
#define DELAY 0

using namespace std;

#include "./Bibliotecas/tabuleiro.h"
#include "./Bibliotecas/posicao.h"
#include "./Bibliotecas/jogo.h"
#include "./Bibliotecas/auxiliares.h"
#include "./Bibliotecas/random.h"
#include "./Bibliotecas/analisador.h"
#include "./Bibliotecas/desenhos.h"

int pecasNoInicio(Player p);
void posicionarCursorNoMeio();
void darZoom(int a);
int vezDoProximo(int vezAtual, Player p[]);
void sequencial(int num, int vetor[]);

int main()
{

    darZoom(7);

    system("chcp 65001");
    system("MODE con cols=80 lines=22");
    clrscr();

    char tabuleiro[LINHAS][COLUNAS];
    Player players[4];
    iniciarTabuleiro(tabuleiro);

    //TELA DE SELECIONAR MODO DE JOGO
    int mode = 0, numplayers;
    cout << "Digite o numero de players: ";
    cin >> mode;
    system("cls");

    if      (mode == 2)
    {
        /// Cria��o dos jogares. Isso n�o pode sair do programa
        /// Passa o jogador que vc quer criar, o nome dele, o tabuleiro e se ele vai ou n�o jogar;
        /// A� vc faz um jeito de perguntar quantos v�o jogar e atribui o ultimo elemento com true ou false

        //DOIS PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, false);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, false);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 2;
    }
    else if (mode == 3)
    {
        //TRES PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, false);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 3;
    }
    else if (mode == 4)
    {
        //QUATRO PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, true);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 4;
    }
    else if (mode == 5)
    {
        //CINCO PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, true);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 4;
    }
    
    int vetorseq[4];
    sequencial(numplayers, vetorseq);
    printTabuleiro(tabuleiro);

    //LACOS DE PARTIDA
    desenhar_quadrado(40, 20, 35, 0);
    while (1)
    {   
        for (int ind = 0; ind < numplayers; ind++) //utilizar o indice desse vetor para direcionar jogador
        {
            // BLOCO DE JOGADA PARA CADA JOGADOR
            preencher_com_espacos(38, 13, 36, 1);
            gotoxy(40, 2);
            printf("Vez do jogador: %s", players[vetorseq[ind]].nome);
            desenhar_linha_horizontal(37, 3, 36);
            jogamentos(players, vetorseq[ind], tabuleiro, pecasNoInicio(players[vetorseq[ind]]), 4 - players[vetorseq[ind]].pecasEmJogo, 36, 0);
            //condição de vencedor para parar o jogo e printar o vencedor
            getch();
        }
    }

    printTabuleiro(tabuleiro);

    return 0;
}

void posicionarCursorNoMeio()
{
    SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
}

void darZoom(int a)
{
    keybd_event(VK_LCONTROL, 0x36, 0, 0);

    for (int i = 0; i < a; i++)
    {
        posicionarCursorNoMeio();
        mouse_event(MOUSEEVENTF_WHEEL, MOUSEEVENTF_ABSOLUTE, MOUSEEVENTF_ABSOLUTE, WHEEL_DELTA, NULL);
    }
    keybd_event(VK_LCONTROL, 0x1C, KEYEVENTF_KEYUP, 0);
}


int pecasNoInicio(Player p)
{
    int temp = 0;
    for(int i = 0; i < 4; i++)
    {
        if(p.piece[i].estaNaPosicaoInicial)
            temp++;
    }
    return temp;
}




int vezDoProximo(int vezAtual, Player p[])
{
    /*vezDoProximo recebe o jogador da vez e o vetor de jogadores
    retorna o proximo a jogar*/
    int resultado;
    if (vezAtual == VERMELHO)
        vezAtual = -1;

    for (int i = vezAtual + 1; i < 4; i++)
    {
        if (i == 2)
        {
            if (p[AZUL].vaiJogar)
                return AZUL;
            else
                continue;
        }

        else if (i == 3)
        {
            if (p[VERMELHO].vaiJogar)
                return VERMELHO;
            else
                i = -1;
        }
        else
        {
            if (p[i].vaiJogar)
                return i;
        }
    }

    return -1;
}

void sequencial(int num, int vetor[])
{
    if (num == 2)
    {
        vetor[0] = 2;
        vetor[1] = 1;
    }
    else if (num == 3)
    {
        vetor[0] = 2;
        vetor[1] = 0;
        vetor[2] = 1;
    }
    else
    {
        vetor[0] = 2;
        vetor[1] = 0;
        vetor[2] = 1;
        vetor[3] = 3;
    }
}