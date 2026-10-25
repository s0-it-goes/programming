#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

bool checkRow(int arr[SIZE][SIZE], unsigned char strNumber)
{
    for(unsigned char i = 0; i < SIZE - 1; i++)
    {
        for(unsigned char j = i + 1; j < SIZE; j++)
        {
            if(arr[strNumber][i] == arr[strNumber][j]) // сравниваем каждый элемент один раз
                return false;
            
        }
    }

    return true;
}

bool checkCol(int arr[SIZE][SIZE], unsigned char colNumber)
{
    for(unsigned char i = 0; i < SIZE - 1; i++)
    {
        for(unsigned char j = i + 1; j < SIZE; j++)
        {
            if(arr[i][colNumber] == arr[j][colNumber]) // сравниваем каждый элемент один раз
                return false;
            
        }
    }

    return true;
}

// функция проходит по каждому элементу и сравнивает их между собой(включая самих себя), всего 3^4(81) прогонов
bool checkSquare(int arr[SIZE][SIZE], unsigned char row, unsigned char col) 
{
    unsigned char cnt = 0; //счётчик, который смотрит, сколько раз сравнивал с одинаковым значением(должен быть 9, т.к. один раз цикл сравнивает сам с собой)

    for(unsigned char i = 0; i < 3; i++)
    {
        for(unsigned char j = 0; j < 3; j++)
        {
            for(unsigned char k = 0; k < 3; k++)
            {
                for(unsigned char l = 0; l < 3; l++)
                {
                    if(arr[i + row][j + col] == arr[k + row][l + col])
                        cnt += 1;
                }
            }
        }
    }

    if(cnt == 9) // счётчик равен 9, т.к. в матрице 3 на 3 всего 9 элементов, и каждый элемент сранивается 1 раз сам с собой
        return true;
    else
        return false;
}

bool isValidSudoku(int arr[SIZE][SIZE])
{
    for(unsigned char i = 0; i < SIZE; i++)
    {
        if(!checkRow(arr, i))
            return false;
        if(!checkCol(arr, i))
            return false;
    }

    for(unsigned char i = 0; i < 9; i += 3) // шаг +3, т.к. нужно сранивать матрицы 3 на 3
    {
        for(unsigned char j = 0; j < 9; j += 3)
        {
            if(!checkSquare(arr, i, j))
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int sudoku[SIZE][SIZE] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 5, 9}
    };
    
    if(isValidSudoku(sudoku))
        printf("Матрица является судоку\n");
    else
        printf("Матрица не является судоку\n");

    return 0;
}