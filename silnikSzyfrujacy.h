#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabulaRecta.h"

void szyfrowanie(char operacja,
                    char nazwaPlikuWejsciowego[],
                    char nazwaPlikuWyjsciowego[],
                    char klucz[]);

void deszyfrowanie(char operacja,
                    char nazwaPlikuWejsciowego[],
                    char nazwaPlikuWyjsciowego[],
                    char klucz[]);

void silnikSzyfrujacy(char operacja,
                        char nazwaPlikuWejsciowego[],
                        char nazwaPlikuWyjsciowego[],
                        char klucz[],
                        char kryptoanaliza);
