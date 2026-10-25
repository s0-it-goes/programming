#include <stdio.h>

#define SIZE 15

void max(int arr[], char size)
{
    int max = arr[0];
    char day = 0;

    for(char i = 0; i < size; i++)
    {
        if(max < arr[i])
        {
            day = i+1;
            max = arr[i];
        }
    }

    printf("max: %d, day: %d\n", max, day);
}

void min(int arr[], char size)
{
    int min = arr[0];
    char day = 0;

    for(char i = 0; i < size; i++)
    {
        if(min > arr[i])
        {
            day = i+1;
            min = arr[i];
        }
    }

    printf("min: %d, day: %d\n", min, day);
}

void raise(int arr[], char size)
{
    int cnt = 0;
    char maxCnt = cnt;

    for(char i = 0; i < size - 1; i++)
    {
        if(arr[i] <= arr[i+1])
        {
            cnt += 1;
            maxCnt = cnt > maxCnt ? cnt : maxCnt;
        }
        else
            cnt = 0;

    }

    printf("Самый длинный период роста: %d дней\n", maxCnt);
}

void settle(int arr[], int size)
{
    int diff = 0;
    int maxDiff = 0;

    char start = 0;
    char end = 0;

    for(int i = 0; i < size - 1; i++)
    {
        for(int j = i+1; j < size; j++)
        {

            diff = arr[i] - arr[j];

            if(diff > maxDiff)
            {
                maxDiff = diff;
                start = i+1;
                end = j+1;
            }
        }
    }

    if(end == -1)
        end = SIZE;
    
    printf("Максимальная просадка: %d, начало просадки: %d, конец просадки: %d\n", maxDiff, start, end);
}

int main()
{
    int price[SIZE] = {100, 102, 105, 103, 98, 96, 99, 104, 110, 108, 112, 118, 115, 111, 117};
    


    max(price, SIZE);
    min(price, SIZE);
    raise(price, SIZE);
    settle(price, SIZE);

    return 0;
}