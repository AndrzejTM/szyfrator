// Autor: Andrzej Matuszczyk
// Data: 11.05.2018

// ATM_Viegenere to program służący do szyfrowania i deszyfrowania plików tekstowych
// z wykorzystaniem algorytmu Viegenere'a.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabulaRecta.h"
#include "silnikSzyfrujacy.h"

void pomoc()
{
    printf("Szyfr Vigenere.\n");
    printf("-f => plik wejściowy\n");
    printf("-o => plik wyjściowy\n");
    printf("-e => szyfrowanie\n");
    printf("-d => deszyfrowanie\n");
    printf("-k => klucz\n");
    printf("-a => kryptoanaliza\n");
    printf("-p => pomoc");

}

int main(int argc, char **argv)
{
    char operacja = '0';
    char nazwaPlikuWejsciowego[50];
    char nazwaPlikuWyjsciowego[50];
    char klucz[100] = "0";
    char kryptoanaliza = '0';
    for (int i=0; i<argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            operacja='d';
        }
        if (strcmp(argv[i], "-e") == 0)
        {
            operacja='e';
        }
        if (strcmp(argv[i], "-f") == 0)
        {
            strcpy(nazwaPlikuWejsciowego, argv[i+1]);
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            strcpy(nazwaPlikuWyjsciowego, argv[i+1]);
        }
        if (strcmp(argv[i], "-k") == 0)
        {
            strcpy(klucz, argv[i+1]);
        }
        if (strcmp(argv[i], "-a") == 0)
        {
            kryptoanaliza='1';
        }
        if (strcmp(argv[i], "-p") == 0)
        {
            pomoc();
        }
        //printf("%s\n", argv[i]);
    }

    silnikSzyfrujacy(operacja, nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, klucz, kryptoanaliza);
    return 0;
}
