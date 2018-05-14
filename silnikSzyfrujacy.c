#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tabulaRecta.h"


// Funkcja szyfrująca
int szyfrowanie(char operacja,
                    char nazwaPlikuWejsciowego[],
                    char nazwaPlikuWyjsciowego[],
                    char klucz[])
{
    char tabulaRecta[MAX_ROWS][MAX_COLS];
    generujTabulaRecta(tabulaRecta);
    int keyLenght = strlen(klucz);

    // Otwarcie pliku z tekstem do zaszyfrowania
        FILE *plikWe = fopen(nazwaPlikuWejsciowego, "r");
        if (plikWe == NULL)
        {
            printf("Nie udało się otworzyć pliku z tekstem do zaszyfrowania.\n");
            return -1;
        }
        else
        {
            printf("Udało się otworzyć plik z tekstem do zaszyfrowania\n");
        }

        // Obliczenie ilości znaków w pliku z tekstem do zaszyfrowania
        int counter = 0;
        while (!feof(plikWe))
        {
            fgetc(plikWe);
            counter++;
        }

        // Alokacja bufora przechowującego tekst z pliku z tekstem do zaszyfrowania
        int *tekst = (int*)malloc(sizeof(int)*counter);
        if (tekst == NULL)
        {
            printf("Nie udało się zaalokować tablicy 'tekst'");
            return -1;
        }

        rewind(plikWe);
        int i = 0;
        int c = 0;
        // Wszystkie znaki w buforze przechowującym tekst z pliku mają być zapisane DUŻYMI LITERAMI
        while (!feof(plikWe))
        {
            c = toupper(fgetc(plikWe));
            tekst[i]=c;
            i++;
        }
        // Zamknięcie pliku z tekstem, teraz operujemy tylko na buforze przechowującym tekst
        if (plikWe!=NULL)
        {
            fclose(plikWe);
        }

        // Alokacja tablicy pomocniczej przy szyfrowaniu. Znaki z bufora są pokryte kluczem
        int *pokrytyKluczem = (int*)malloc(sizeof(int)*counter);
        if (pokrytyKluczem == NULL)
        {
            printf("Nie udało się zaalokować tablicy 'pokrytyKluczem'");
            free(tekst);
            return -1;
        }
        // Alokacja tablicy docelowej, w której znajdzie się zaszyfrowany tekst
        int *zakodowanyTekst = (int*)malloc(sizeof(int)*counter);
        if (zakodowanyTekst == NULL)
        {
            printf("Nie udało się zaalokować tablicy 'zakodowanyTekst'");
            free(tekst);
            free(pokrytyKluczem);
            return -1;
        }
        int charCounter = 0;

        i=0;

        // Wypisanie niezaszyfrowanego tekstu z bufora
        while (tekst[i]!='\0')
        {
            printf("%c", tekst[i]);
            i++;
        }
        printf("\n");
        i=0;

        // Pokrycie tekstu kluczem (zapisanie tablicy pokrytyKluczem)
        while (tekst[i]!='\0')
        {
            if (tekst[i] == ' ' || ( tekst[i]>'Z' || tekst[i]<'A' ))
            {
                pokrytyKluczem[i] = ' ';
            }
            else
            {
                pokrytyKluczem[i] = klucz[charCounter%keyLenght];
                charCounter++;
            }
            printf("%c", pokrytyKluczem[i]);
            i++;
        }
        printf("\n");


        i=0;

        // Zakodowanie tekstu. Pracujemy na tabluaRecta. Bierzemy literę tekstu niezakodowanego
        // i przypisujemy ją wierszowi tabulaRecta. Bierzemy literę z tablicy pokrytykluczem
        // i przypisujemy ją kolumnie. Litera na przecięku wiersza i kolumny to zaszyfrowana litera tekstu
        for (int i=0; i<counter; i++)
        {
            if ( tekst[i]>'Z' || tekst[i]<'A' )
            {
                zakodowanyTekst[i] = ' ';
            }
            else
            {
                zakodowanyTekst[i] = tabulaRecta[tekst[i]-'A'][pokrytyKluczem[i]-'A'];
                //charCounter++;
            }
            printf("%c", zakodowanyTekst[i]);
        }

        printf("\n");

        // Otwieramy plik do zapisu zaszyfrowanego tekstu
        FILE *plikWy = fopen(nazwaPlikuWyjsciowego, "w");
        if (plikWy==NULL)
        {
            printf("Nie udało się otworzyć pliku do przechowywania zakodowanego tekstu.\n");
            free(tekst);
            free(pokrytyKluczem);
            free(zakodowanyTekst);
            return -1;
        }
        else
        {
            printf("Udało się otworzyć plik do przechowywania zakodowanego tekstu.\n");
        }

        // Zapisujemy zaszyfrowany tekst
        while (zakodowanyTekst[i]!='\0')
        {
            fputc(zakodowanyTekst[i], plikWy);
            i++;
        }

        // Zwalniamy tablice z tekstem, pokrytą kluczem i z zakodowanym tekstem
        free(tekst);
        free(pokrytyKluczem);
        free(zakodowanyTekst);

        // Zamykamy plik wyjściowy
        fclose(plikWy);
        return 0;
}

// Funkcja deszyfrująca
int deszyfrowanie(char operacja,
                    char nazwaPlikuWejsciowego[],
                    char nazwaPlikuWyjsciowego[],
                    char klucz[])
{
    char tabulaRecta[MAX_ROWS][MAX_COLS];
    generujTabulaRecta(tabulaRecta);
    int keyLenght = strlen(klucz);

    // Otwieramy plik z zaszyfrowanym tekstem
    FILE *plikWe = fopen(nazwaPlikuWejsciowego, "r");
        if (plikWe == NULL)
        {
            printf("Nie udało się otworzyć pliku z zaszyfrowanym tekstem.\n");
            return -1;
        }
        else
        {
            printf("Udało się otworzyć plik z zaszyfrowanym tekstem.\n");
        }

        // Obliczamy ilość znaków w pliku z zaszyfrowanym tekstem
        int counter = 0;
        while (!feof(plikWe))
        {
            fgetc(plikWe);
            counter++;
        }

        // Alokujemy tablicę do przechowywania zaszyfrowanego tekstu
        int *tekst = (int*)malloc(sizeof(int)*counter);
        if (tekst == NULL)
        {
            printf("Nie udało się zaalokować tablicy 'tekst'");
            return -1;
        }
        rewind(plikWe);
        int i = 0;
        int c = 0;

        // Wszystkie znaki w zaszyfrowanego tekstu muszą być zapisane DUŻYMI LITERAMI
        while (!feof(plikWe))
        {
            c = toupper(fgetc(plikWe));
            tekst[i]=c;
            i++;
        }

        // Zamykamy plik wejściowy, teraz pracujemy tylko na tablicy z zaszyfrowanym tekstem
        if (plikWe!=NULL)
        {
            fclose(plikWe);
        }

        // Alokujemy tablicę pomocniczą do pokrycia zaszyfrowanego tekstu kluczem
        int *pokrytyKluczem = (int*)malloc(sizeof(int)*counter);
        if (pokrytyKluczem == NULL)
        {
            printf("Nie udało się zaalokować tablicy 'pokrytyKluczem'");
            free(tekst);
            return -1;
        }
        // Alokujemy tablicę do przechowywania odkodowanego tekstu
        int *odkodowanyTekst = (int*)malloc(sizeof(int)*counter);
        if (odkodowanyTekst == NULL)
        {
            printf("Nie udało się zaalokować tablicy 'odkodowanyTekst'");
            free(tekst);
            free(pokrytyKluczem);
            return -1;
        }
        int charCounter = 0;

        i=0;

        // Wypisujemy zaszyfrowany tekst
        while (tekst[i]!='\0')
        {
            printf("%c", tekst[i]);
            i++;
        }
        printf("\n");

        i=0;

        // Pokrywamy zaszyfrowany tekst kluczem
        while (tekst[i]!='\0')
        {
            if ( tekst[i]>'Z' || tekst[i]<'A' )
            {
                pokrytyKluczem[i] = ' ';
            }
            else
            {
                pokrytyKluczem[i] = klucz[charCounter%keyLenght];
                charCounter++;
            }
            printf("%c", pokrytyKluczem[i]);
            i++;
        }
        printf("\n");

        i=0;

        // Deszyfrujemy zakodowany tekst. Wykorzystujemy tablicę tabulaRecta. Bierzemy literę z tablicy pokrytyKluczem i ustawiamy
        // na kolumnie tabulaRecta. Następnie szukamy w tej kolumnie litery z tablicy z zaszyfrowanym tekstem. Pierwsza litera wiersza
        // przecięciu litery z pokrytyKluczem i litery z tekstu zaszyfrowanego to odkodowana litera.
        while (tekst[i]!='\0')
        {
            if (tekst[i]>'Z' || tekst[i]<'A')
            {
                odkodowanyTekst[i] = ' ';
            }
            else
            {
                for (char A='A'; A<='Z'; A++)
                {
                    if (tabulaRecta[A-'A'][pokrytyKluczem[i]-'A'] == tekst[i])
                    {
                        odkodowanyTekst[i]=A;
                        break;
                    }
                }
            }
            printf("%c", odkodowanyTekst[i]);
            i++;
        }
        printf("\n");

        // Otwieramy plik do zapisu odkodowanego tekstu
        FILE *plikWy = fopen(nazwaPlikuWyjsciowego, "w");
        if (plikWy==NULL)
        {
            printf("Nie udało się otworzyć pliku do przechowywania odkodowanego tekstu.\n");
            free(tekst);
            free(pokrytyKluczem);
            free(odkodowanyTekst);
            return -1;
        }
        else
        {
            printf("Udało się otworzyć plik do przechowywania odkodowanego tekstu.\n");
        }

        i=0;

        // Zapisujemy odkodowany tekst do pliku
        while(odkodowanyTekst[i]!='\0')
        {
            fputc(odkodowanyTekst[i], plikWy);
            i++;
        }

        // Zwalniamy tablicę z tekstem zakodowanym, pokrytą kluczem i z odkodowanym tekstem
        free(tekst);
        free(pokrytyKluczem);
        free(odkodowanyTekst);

        // Zamykamy plik wyjściowy
        fclose(plikWy);
        return 0;
}

// Funkcja silnikSzyfrujący agregująca funkcję szyfrującą i deszyfrującą.
// Dodatkowo umożliwia kryptoanalizę z wykorzystaniem tabulaRecta
void silnikSzyfrujacy(char operacja,
                        char nazwaPlikuWejsciowego[],
                        char nazwaPlikuWyjsciowego[],
                        char klucz[],
                        char kryptoanaliza)
{
    printf("Uruchomiono silnik szyfrujący.\n");
    char tabulaRecta[MAX_ROWS][MAX_COLS];
    generujTabulaRecta(tabulaRecta);
    int keyLenght = strlen(klucz);

    // Litery klucza muszą być zapisane DUŻYMI LITERAMI
    for (int i=0; i<keyLenght; i++)
    {
        klucz[i]=toupper(klucz[i]);
    }

    // Włączenie kryptoanalizy. Użytkownik może samodzielnie szyfrować i deszyfrować
    // tekst na wyświetlonej tabulaRecta
    if (kryptoanaliza=='1')
    {
        wyswietlTabulaRecta(tabulaRecta);
    }

    // Włączenie operacji szyfrowania
    if (operacja=='e')
    {
        szyfrowanie(operacja, nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, klucz);
    }

    // Włączenie operacji deszyfrowania
    if (operacja == 'd')
    {
        deszyfrowanie(operacja, nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, klucz);
    }
}

