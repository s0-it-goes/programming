#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 4

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

void showMatrix(unsigned short **matrix, unsigned char size, unsigned int score)
{
    for(unsigned char i = 0; i < size; i++)
    {     
        for(unsigned char j = 0; j < size; j++)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nscore: %d\n", score);
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


unsigned int mergeSimilar(unsigned short **matrix, unsigned char size)
{
    unsigned int score = 0;
    for(unsigned char i = 0; i < size; i++)
    {
        for(unsigned char j = 0; j < size - 1; j++)
        {
            if (matrix[i][j] != 0 && matrix[i][j] == matrix[i][j+1])
            {
                matrix[i][j] *= 2;
                matrix[i][j+1] = 0;
                
                score += matrix[i][j];
            }
        }
    }

    return score;
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

unsigned int moveLeft(unsigned short **matrix, unsigned char size)
{
    move(matrix, size);
    unsigned int score = mergeSimilar(matrix, size);
    move(matrix, size);

    return score;
}

unsigned int moveRight(unsigned short **matrix, unsigned char size)
{
    reflectMatrix(matrix, size);
    unsigned int score = moveLeft(matrix, size);
    reflectMatrix(matrix, size);

    return score;
}

unsigned int moveUp(unsigned short **matrix, unsigned char size)
{
    transposeMatrix(matrix, size);
    unsigned int score = moveLeft(matrix, size);
    transposeMatrix(matrix, size);

    return score;
}

unsigned int moveDown(unsigned short **matrix, unsigned char size)
{
    transposeMatrix(matrix, size);
    reflectMatrix(matrix, size);
    unsigned int score = moveLeft(matrix, size);
    reflectMatrix(matrix, size);
    transposeMatrix(matrix, size);
    
    return score;
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
/*
bool isWin(unsigned short **matrix, unsigned char size)
{
    for (unsigned char i = 0; i < size; i++)
    {
        for (unsigned char j = 0; j < size; j++)
        {
            if (matrix[i][j] == 2048)
            {
                return true;
            }
        }
    }

    return false;
}
*/

void addToHistory(unsigned short **matrix, unsigned char size, unsigned int score, unsigned short ****history, unsigned int **scores, unsigned short mem)
{
    *history = realloc(*history, mem * sizeof(**history));
    *scores = realloc(*scores, mem * sizeof(**scores));

    (*history)[mem-1] = copyMatrix(matrix, size);
    (*scores)[mem-1] = score;
}

void undo(unsigned short ***matrix, unsigned char size, unsigned int *score, unsigned short ***history, unsigned int *scores, unsigned short *mem)
{
    if((*mem) <= 1)
        return;

    freeMatrix(*matrix, size);
    freeMatrix(history[(*mem)-1], size);
    (*mem)--;

    *matrix = copyMatrix((history)[(*mem)-1], size);

    *score = scores[(*mem)-1];
}

void play(unsigned short **matrix, unsigned char size, unsigned char move, unsigned int *score, unsigned short ****history, unsigned int **scores, unsigned short *mem)
{
    unsigned short **copy = copyMatrix(matrix, size);
    
    switch(toupper(move))
    {
        case 'W':
            *score += moveUp(matrix, size);
            break;
        case 'A':
            *score += moveLeft(matrix, size);
            break;
        case 'S':
            *score += moveDown(matrix, size);
            break;
        case 'D':
            *score += moveRight(matrix, size);
            break;
        default:
            break;
    }

    if(!compareMatrix(matrix, copy, size))
    {
        spawnNew(matrix, size);
        (*mem)++;
        addToHistory(matrix, size, *score, history, scores, *mem);
    }
    
    printf("\033[H\033[J");
    showMatrix(matrix, size, *score);

    freeMatrix(copy, size);
    
}

int main()
{
    //  выбираю два изначальных положения двоек.
    srand(time(NULL));
    
    unsigned short **matrix = startMatrix(SIZE);

    unsigned short ***history = NULL;
    unsigned int *scores = NULL;
    unsigned short mem = 1;

    unsigned int score = 0;
    unsigned char c = 0;

    addToHistory(matrix, SIZE, score, &history, &scores, mem);

    printf("\033[H\033[J");
    showMatrix(matrix, SIZE, 0);


    while(true)
    {
        scanf(" %c", &c); // пробел перед %c нужен, чтобы пропускать все пробельные символы после ввода символа

        if(toupper(c) == 'Q')
        {
            break;
        }

        if (toupper(c) == 'B')
        {
            undo(&matrix, SIZE, &score, history, scores, &mem);
            printf("\033[H\033[J");
            showMatrix(matrix, SIZE, score);
            continue;
        }

        play(matrix, SIZE, c, &score, &history, &scores, &mem);

        

        if(!anyMoves(matrix, SIZE))
        {
            printf("GAME OVER\n");
            break;
        }
    }

    for (unsigned short i = 0; i < mem; i++)
        freeMatrix(history[i], SIZE);

    free(history);
    free(scores);
    freeMatrix(matrix, SIZE);

    return 0;
}