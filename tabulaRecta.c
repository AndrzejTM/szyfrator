#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 26
#define MAX_COLS 26

void generujTabulaRecta(char tabulaRecta[MAX_ROWS][MAX_COLS])
{
    int pos, row, col;

    for (row=0; row<MAX_ROWS; row++)
    {
        pos = 0;
        for (col=0; col<MAX_COLS; col++)
        {
            if ('A'+row+col > 'Z' && row > 0)
                {
                    tabulaRecta[row][col] = 'A'+pos;
                    pos++;
                }
            else if  ('A' + row+col == 'Z')
                {
                    tabulaRecta[row][col] = 'Z';
                }
            else
                {
                    tabulaRecta[row][col] = 'A'+row+col;
                }
        }
    }
}

void wyswietlTabulaRecta(char tabulaRecta[MAX_ROWS][MAX_COLS])
{
    int row, col;
    printf("Tabula Recta:\n");
    for (row=0; row<MAX_ROWS; row++)
    {
        for (col=0; col<MAX_COLS; col++)
        {
            printf("%c", tabulaRecta[row][col]);
        }
        printf("\n");
    }
}
