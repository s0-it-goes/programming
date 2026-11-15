#include <stdio.h>
#include <ctype.h>
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
        unsigned char line  = (rand() % size); 
        unsigned char col   = (rand() % size);
        
        if(matrix[line][col] != 0){ 
            // проверка на случай, если выпадут два одинаковых элемента - будет повторяться, пока второй не выпадет отличным от первого
            i--;
            continue;
        }

        matrix[line][col] = 2;
    }

    return matrix;
}



void mergeSimilar(unsigned short **matrix, unsigned char size)
{
    for(unsigned char i = 0; i < size; i++)
    {
        for(unsigned char j = 0; j < size - 1; j++)
        {
            if (matrix[i][j] == matrix[i][j+1])
            {
                matrix[i][j] *= 2;
                matrix[i][j+1] = 0;
            }
        }
    }
}

void spawnNew(unsigned short **matrix, unsigned char size)
{
    bool flag = true;
    while(flag)
    {
        unsigned char line  = (rand() % size); 
        unsigned char col   = (rand() % size);
        
        if(matrix[line][col] != 0){ 
            // проверка на случай, если на рандомно выбранной ячейке уже есть число
            continue;
        }

        matrix[line][col] = 2;
        flag = false;
    }
}

void reflectMatrix(unsigned short **matrix, unsigned char size)
{
    unsigned short tmp = 0;

    for(unsigned char i = 0; i < size; i++)
    {
        for(unsigned char j = 0; j < size / 2; j++)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[i][size-j-1];
            matrix[i][size-j-1] = tmp;
        }
    }
}

void transposeMatrix(unsigned short **matrix, unsigned char size)
{
    unsigned short tmp = 0;

    for(unsigned char i = 0; i < size; i++)
    {
        for(unsigned char j = i+1; j < size; j++)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}

void moveLeft(unsigned short **matrix, unsigned char size)
{
    short zeroIndex = -1;
    for(unsigned char i = 0; i < size; i++)
    {
        for(unsigned char j = 0; j < size; j++)
        {
            if(matrix[i][j] == 0 && zeroIndex == -1)
                zeroIndex = j;
            
            if(matrix[i][j] != 0 && zeroIndex >= 0)
            {
                matrix[i][zeroIndex] = matrix[i][j];
                matrix[i][j] = 0;
                zeroIndex += 1; // по шагам: 2 0 4 2 -> 2 4 0 2 -> 2 4 2 0, т.е по сути надо найти первый ноль, 
                                // а потом добавлять +1 к нему, если произошел сдвиг влево
            }
        }
        zeroIndex = -1;
    }
}

void moveRight(unsigned short **matrix, unsigned char size)
{
    reflectMatrix(matrix, size);
    moveLeft(matrix, size);
    reflectMatrix(matrix, size);
}

void moveUp(unsigned short **matrix, unsigned char size)
{
    transposeMatrix(matrix, size);
    moveLeft(matrix, size);
    transposeMatrix(matrix, size);
}

void moveDown(unsigned short **matrix, unsigned char size)
{
    
    transposeMatrix(matrix, size);
    reflectMatrix(matrix, size);
    moveLeft(matrix, size);
    reflectMatrix(matrix, size);
    transposeMatrix(matrix, size);
}

void showMatrix(unsigned short **matrix, unsigned char size)
{
    for(unsigned char i = 0; i < SIZE; i++)
    {     
        for(unsigned char j = 0; j < SIZE; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void play(unsigned short **matrix, unsigned char size, unsigned char move)
{
    printf("\033[H\033[J");
    switch(toupper(move))
    {
        case 'W':
            break;
        case 'A':
            break;
        case 'S':
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

    printf("\n");
    showMatrix(matrix, SIZE);
    

    
    

    for(unsigned char i = 0; i < SIZE; i++)
    {
        free(matrix[i]);
    }
    
    free(matrix);

    return 0;
}