#include <iostream>
#include <cstdio>
#include "./Bibliotecas/random.h"
#include "./Bibliotecas/analisador.h"
#include <time.h>
using namespace std;

int main()
{
    srand((unsigned)time(NULL));

    int vetor[10], numb1, numb2, an;

    while (1)
    {
        zerarvetor(vetor, 3);
        random_numbers(vetor, 3);
        cout << "Digite o numero de tokens dentro da casa: ";
        cin >> numb1;
        cout << "Digite o numero de tokens que chegaram ao fim: ";
        cin >> numb2;
        jogamentos(numb1, numb2, 1, 1);
        cout << "Continue? ";
        cin >> an;
        if (an == 0)
        {
            break;
        }
    }

    return 0;
}
