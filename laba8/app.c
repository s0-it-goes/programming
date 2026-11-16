#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 2

void spawnNew(unsigned short **matrix, unsigned char size)
{
    while(true)
    {
        unsigned char line  = (rand() % size); 
        unsigned char col   = (rand() % size);
        
        if(matrix[line][col] != 0){ 
            // проверка на случай, если на рандомно выбранной ячейке уже есть число
            continue;
        }

        matrix[line][col] = 2;
        return;
    }
}

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
        spawnNew(matrix, size);
    }

    return matrix;
}

void showMatrix(unsigned short **matrix, unsigned char size)
{
    for(unsigned char i = 0; i < size; i++)
    {     
        for(unsigned char j = 0; j < size; j++)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(unsigned short **matrix, unsigned char size)
{
    for(unsigned char i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
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

void move(unsigned short **matrix, unsigned char size)
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

void moveLeft(unsigned short **matrix, unsigned char size)
{
    move(matrix, size);
    mergeSimilar(matrix, size);
    move(matrix, size);
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

unsigned short **copyMatrix(unsigned short **matrix, unsigned char size)
{

    unsigned short **copy = malloc(size * sizeof(*copy));

    for(unsigned char i = 0; i < size; i++)
    {
        copy[i] = malloc(size * sizeof(*copy[i]));
        
        for(unsigned char j = 0; j < size; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }

    return copy;
}

bool compareMatrix(unsigned short **matrix1, unsigned short **matrix2, unsigned char size)
{
    for(unsigned char i = 0; i < size; i++)
    {
        for(unsigned char j = 0; j < size; j++)
        {
            if(matrix1[i][j] != matrix2[i][j])
                return false;
        }
    }

    return true;
}

bool anyMoves(unsigned short **matrix, unsigned char size)
{
    unsigned short **copy = copyMatrix(matrix, size);

    moveLeft(copy, size);
    if(!compareMatrix(matrix, copy, size))
    {
        freeMatrix(copy, size);
        return true;
    }

    freeMatrix(copy, size);
    copy = copyMatrix(matrix, size);

    moveRight(copy, size);
    if(!compareMatrix(matrix, copy, size))
    {
        freeMatrix(copy, size);
        return true;
    }
    
    freeMatrix(copy, size);
    copy = copyMatrix(matrix, size);

    moveUp(copy, size);
    if(!compareMatrix(matrix, copy, size))
    {
        freeMatrix(copy, size);
        return true;
    }

    freeMatrix(copy, size);
    copy = copyMatrix(matrix, size);

    moveDown(copy, size);
    if(!compareMatrix(matrix, copy, size))
    {
        freeMatrix(copy, size);
        return true;
    }

    freeMatrix(copy, size);

    return false; // нет доступных ходов

}

void play(unsigned short **matrix, unsigned char size, unsigned char move)
{
    unsigned short **copy = copyMatrix(matrix, size);
    
    switch(toupper(move))
    {
        case 'W':
            moveUp(matrix, size);
            break;
        case 'A':
            moveLeft(matrix, size);
            break;
        case 'S':
            moveDown(matrix, size);
            break;
        case 'D':
            moveRight(matrix, size);
            break;
        default:
            break;
    }

    if(!compareMatrix(matrix, copy, size))
        spawnNew(matrix, SIZE);
    
    printf("\033[H\033[J");
    showMatrix(matrix, size);

    freeMatrix(copy, size);
}

int main()
{
    //  выбираю два изначальных положения двоек.
    srand(time(NULL));
    
    unsigned short **matrix = startMatrix(SIZE);

    printf("\033[H\033[J");
    showMatrix(matrix, SIZE);

    unsigned char c = 0;
    while(true)
    {
        scanf(" %c", &c); // пробел перед %c нужен, чтобы пропускать все пробельные символы после ввода символа
        play(matrix, SIZE, c);

        if(toupper(c) == 'Q')
        {
            break;
        }

        if(!anyMoves(matrix, SIZE))
        {
            printf("GAME OVER\n");
            break;
        }
    }

    freeMatrix(matrix, SIZE);

    return 0;
}