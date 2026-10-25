#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int **calculateMinor(int **arr, unsigned char N, unsigned char el)
{
    // выделяю память для массива указателей на строки
    int **minor = (int **) malloc((N - 1) * sizeof(int *));

    // выделяю память для каждой строки 
    for(unsigned char i = 0; i < N - 1; i++)
    {
        minor[i] = (int *) malloc((N - 1) * sizeof(int));
    }
    
    bool isSkipped = false; //флаг, показывающий, пропустили ли мы столбец, в котором находится элемент, по которому раскладываем матрицу на минор

    /*
        проходимся по исходной матрице, пропуская первую(нулевую) строку, по которой раскладываем массив на миноры, и пропуская элемент, по которому
        раскладываем матрицу на минор в данной итерации
    */
    for(unsigned char i = 1; i < N; i++)
    {
        for(unsigned char j = 0; j < N; j++)
        {
            if(j == el) 
            {
                isSkipped = true;
                continue; // пропускаем столбец, в котором находится элемент, по которому раскладываем матрицу
            }

            if(isSkipped)
                minor[i-1][j-1] = arr[i][j]; // ну и если уже пропустили итерацию, то в массиве, в который записываем минор, нужно делать j-1
            else
                minor[i-1][j] = arr[i][j];
        }
        isSkipped = false;
    }

    //отладочный вывод миноров
    /*
    printf("Минор:\n");
    for(unsigned char i = 0; i < N-1; i++)
    {
        for(unsigned char j = 0; j < N-1; j++)
        {
            printf("%d   ", minor[i][j]);
        }
        printf("\n");
    }
    */
    return minor;
}

//функция, которая считает определитель матрицы 2х2

double countMinorDeterminant(int **arr, unsigned char size)
{
    double result = ((double)arr[0][0] * (double)arr[1][1]) - ((double)arr[0][1] * (double)arr[1][0]);

    return result;
}

// функция, которая считает определитель всей матрицы, рекурсивно вызывая себя, если в данный момент матрица размера больше или равна 3.
double countDeterminant(int **arr, unsigned char N)
{
    double det = 0;

    if(N == 1) // вызывается только если в матрице 1 элемент
        return arr[0][0];
    
    if(N == 2) // рекурсия доходит до сюда
        return countMinorDeterminant(arr, N);
    
    if(N >= 3) // рекурсивный шаг
    {
        for(unsigned char i = 0; i < N; i++)
        {
            int **minor = calculateMinor(arr, N, i);
            // считаем определитель с учётом чётности позиции элемента, по которому раскладываем
            det += i % 2 == 0 ? arr[0][i] * countDeterminant(minor, N-1) : arr[0][i] * countDeterminant(minor, N-1) * (-1); 

            for(unsigned char j = 0; j < N-1; j++)
            {
                free(minor[j]);
            }
            free(minor); // освобождаю память массива, содержащего минор
            minor = NULL; // обнуляю указатель
        }

        return det;
    }

    return 0;
}

void kramer(int **arr, int *r, int N)
{
    double det = countDeterminant(arr, N);
    if(det == 0) // если определитель оригинальной матрицы равен нулю, то метод крамера использовать нельзя
    {
        printf("Метод крамера неприменим\n");
        return;
    }

    double result = 0;

    for(unsigned char i = 0; i < N; i++)
    {
        // выделяю память для массива, который будет копией массива arr, но столбец i будет заменен на правую часть уравнения
        int **tmp = (int **) malloc(N * sizeof(int *));
        
        for(unsigned char j = 0; j < N; j++)
        {
            tmp[j] = (int *) malloc(N * sizeof(int)); // выделяю память для строк массива
            for(unsigned char k = 0; k < N; k++)
            {
                tmp[j][k] = k == i ? r[j] : arr[j][k];
            }
        }

        result = countDeterminant(tmp, N) / det; // считаем, чему равны переменные системы уравнений

        printf("x[%hhu] = %.2lf\n", i+1, result);


        for(unsigned char u = 0; u < N; u++) 
        {
            free(tmp[u]); // освобождаю память строк 
        }
        free(tmp); // освобождаю память массива указателей
        tmp = NULL;
    }

}

int main()
{
    unsigned char N; // размер массива
    printf("Print N: ");
    scanf("%hhu", &N);

    int **arr = (int **) malloc(N * sizeof(int *)); // выделяю память для массива указателей на строки
    int *r = (int *) malloc(N * sizeof(int)); // выделяю память для массива, хранящего правую часть
    
    if(arr == NULL || r == NULL)
        return -1;

    printf("Заполните систему уравнений:\n");
    for(unsigned char i = 0; i < N; i++)
    {
        arr[i] = (int *) malloc(N * sizeof(int)); // выделяю память для каждой строки массива

        if(arr[i] == NULL)
            return -1;

        printf("строка %hhu:\n", i+1);
        for(unsigned char j = 0; j < N; j++)
        {
            printf("x[%hhu][%hhu]: ", i+1, j+1);
            scanf("%d", &arr[i][j]);
        }
        printf("= ");
        scanf("%d", &r[i]);
    }

    printf("\nИсходная система уравнений: \n");
    for(unsigned char i = 0; i < N; i++)
    {
        for(unsigned char j = 0; j < N; j++)
        {
            printf("%d  ", arr[i][j]);
        }
        printf("= %d", r[i]);
        printf("\n");
    }

    kramer(arr, r, N);

    for(unsigned char i = 0; i < N; i++) 
    {
        free(arr[i]); // освобождаю память строк 
        arr[i] = NULL;
    }
    
    free(arr); // освобождаю память массива указателей на строки
    arr = NULL;

    free(r); // освобождаю память массива 
    r = NULL;

    return 0;
}