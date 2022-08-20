#include <iostream>
#include "./Bibliotecas/gconio.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <time.h>

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
    //srand(time(NULL));
    darZoom(7);

    #ifdef _WIN32
    system("chcp 65001");
    system("MODE con cols=80 lines=22");
    #endif
    clrscr();

    char tabuleiro[LINHAS][COLUNAS];
    Player players[4];
    iniciarTabuleiro(tabuleiro);

    // TELA DE SELECIONAR MODO DE JOGO
    int mode = 0, numplayers;
    cout << "Digite o numero de players: ";
    cin >> mode;
    clrscr();

    int vezDe;

    if (mode == 2)
    {
        /// Cria��o dos jogares. Isso n�o pode sair do programa
        /// Passa o jogador que vc quer criar, o nome dele, o tabuleiro e se ele vai ou n�o jogar;
        /// A� vc faz um jeito de perguntar quantos v�o jogar e atribui o ultimo elemento com true ou false

        // DOIS PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, false);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, false);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 2;
        vezDe = 1;
    }
    else if (mode == 3)
    {
        // TRES PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, false);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 3;
        vezDe = 0;
    }
    else if (mode == 4)
    {
        // QUATRO PLAYERS
        criarJogador(players[VERDE], "VERDE", tabuleiro, VERDE, true);
        criarJogador(players[AZUL], "AZUL", tabuleiro, AZUL, true);
        criarJogador(players[AMARELO], "AMARELO", tabuleiro, AMARELO, true);
        criarJogador(players[VERMELHO], "VERMELHO", tabuleiro, VERMELHO, true);
        numplayers = 4;
        vezDe = rand() % 4;
    }


    printTabuleiro(tabuleiro);

    // LACOS DE PARTIDA
    desenhar_quadrado(40, 20, 35, 0);
    while (1)
    {
        size_t size;
        int * vetor = sortearDados(size);

        bubble_n_sort(vetor, size, 0);

        if(contarNum6(vetor, size) == 3)
        {
            continue;
        }

        for(int i = 0; i < size; i++)
        {
            textcolor(15);
            desenhar_quadrado(40, 20, 35, 0);

            gotoxy(42, 2);
            cout << "Vez de " << players[vezDe].nome;
            viewvector(vetor, size, 40, 6);

            char temp = selecionartoken(players[vezDe], containSix(vetor, size));
            desenhar_quadrado(40, 20, 35, 0);
            int dado = selecionarNumero(vetor, size, temp, players[vezDe]);

            for(int i = 0; i < size; i++)
            {
                if(vetor[i] == dado)
                {
                    vetor[i] = 0;
                    break;
                }
            }
            
            
            int r = andarCasas(tabuleiro, vetor[i], temp, players);
            vetor[i] = 0;

            if(r == -2 || r == 1)
            {
                int aux = i + 1;
                size++;
                vetor = (int*) realloc(vetor, size);
                vetor[aux] = rand() % 6 + 1; 

                while(vetor[aux++] == 6)
                {
                    size++;
                    vetor = (int*) realloc(vetor, size * sizeof(int));
                    vetor[aux] = rand() % 6 + 1; 
                }

            }

            if(players[vezDe].pecasEmJogo == 0)
            {
                cout << "VITORIA";
                return 0;   
            }

            
        }

        vezDe = vezDoProximo(vezDe, players);

        
    }

    printTabuleiro(tabuleiro);

    return 0;
}

#ifdef _WIN32
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
        mouse_event(MOUSEEVENTF_WHEEL, MOUSEEVENTF_ABSOLUTE, MOUSEEVENTF_ABSOLUTE, WHEEL_DELTA, 0);
    }
    keybd_event(VK_LCONTROL, 0x1C, KEYEVENTF_KEYUP, 0);
}

#else

void posicionarCursorNoMeio()
{

}

void darZoom(int a)
{

}

#endif

int pecasNoInicio(Player p)
{
    int temp = 0;
    for (int i = 0; i < 4; i++)
    {
        if (p.piece[i].estaNaPosicaoInicial)
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