#include <stdio.h>

// задача номер 10

int count(int number, char leftBit, char rightBit)
{
    char cnt = 0;
    for(char i = leftBit - 1; i >= rightBit - 1 ; i--)
    {
        char bit = (number >> i) & 1;

        if(bit == 0)
            cnt++;
        
    }

    return cnt;
}

int main()
{
    int a = 251;
    int leftBit = 13;
    int rightBit = 3;
    char cnt = 0;

    
    printf("%d\n", count(a, leftBit, rightBit));

    return 0;
}