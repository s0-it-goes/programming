#include <stdio.h>

// задача номер 15

int swap(unsigned int x, unsigned int y, unsigned char i, unsigned char j)
{
    unsigned int x_bit = (x >> i - 1) & 1; // сдвигаю вправо на i-1 бит и применяю маску 1, чтобы оставить только бит на позиции i
    
    printf("x:");
    for(int i = sizeof(x) * 4 - 1; i > 0; i--)
    {
        printf("%d", (x >> i - 1) & 1);
    }
    printf("\ny:");
    for(int i = sizeof(y) * 4 - 1; i > 0; i--)
    {
        printf("%d", (y >> i - 1) & 1);
    }
   printf("\ni: %d\nj: %d\n", i, j);
    if(x_bit == 1)
    {
        unsigned int y_bit = x_bit << j - 1;  // сдвигаю влево на j-1 бит, чтобы поставить нужный бит из x на позицию j
        printf("y_bit:");
        for(int i = sizeof(y) * 4 - 1; i > 0; i--)
        {
            printf("%d", (y_bit >> i - 1) & 1);
        }

        printf("\ny | y_bit: ");
        for(int i = sizeof(y) * 4 - 1; i > 0; i--)
        {
            printf("%d", ((y | y_bit) >> i - 1) & 1);
        }

        return y | y_bit; // если бит, который хотим переставить равен 1
    }
    else
    {
        unsigned int y_bit = 1u << j - 1;  // сдвигаю влево на j-1 бит, чтобы поставить нужный бит из x на позицию j
        printf("y_bit:");
        for(int i = sizeof(y) * 4 - 1; i > 0; i--)
        {
            printf("%d", (y_bit >> i - 1) & 1);
        }

        printf("\ny | y_bit: ");
        for(int i = sizeof(y) * 4 - 1; i > 0; i--)
        {
            printf("%d", (~(~y | y_bit) >> i - 1) & 1);
        }
        
        return ~(~y | y_bit); // если бит, который хотим переставить равен 0
    }
}

int main()
{
    unsigned int a = 15, b = 17, i = 4, j = 6;
    //swap(a, b, i, j);
    printf("\nresult: %d\n", swap(a, b, i, j));

    return 0;
}