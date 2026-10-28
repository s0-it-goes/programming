#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

unsigned short **startMatrix(unsigned char size)
{
    unsigned short **matrix = malloc(size * sizeof(*matrix));

    for(unsigned char i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(*matrix[i]));
        
        for(unsigned char j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for(unsigned char i = 0; i < 2; i++)
    {
        unsigned char line  = (rand() % size) + 1; 
        unsigned char col   = (rand() % size) + 1;
        
        if(matrix[line - 1][col - 1] != 0){ 
            // проверка на случай, если выпадут два одинаковых элемента - будет повторяться, пока второй не выпадет отличным от первого
            i--;
            continue;
        }

        matrix[line - 1][col - 1] = 2;
    }

    return matrix;
}

void changeMatrix(unsigned short **matrix, unsigned char size, unsigned char move)
{
    switch(toupper(move))
    {
        case 'R':
            break;
        case 'L':
            break;
        case 'U':
            break;
        case 'D':
            break;
        default:
            break;
    }
}


int main()
{
    //  выбираю два изначальных положения двоек.
    srand(time(NULL));
    
    unsigned short **matrix = startMatrix(SIZE);

    for(unsigned char i = 0; i < SIZE; i++)
    {     
        for(unsigned char j = 0; j < SIZE; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }


    for(unsigned char i = 0; i < SIZE; i++)
    {
        free(matrix[i]);
    }
    
    free(matrix);

    return 0;
}