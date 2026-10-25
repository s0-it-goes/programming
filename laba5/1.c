#include <stdio.h>

#define N 2

int main()
{
    float re[N];
    float im[N];
    for(unsigned char i = 0; i < N; i++)
    {
        scanf("%f", &re[i]);
        scanf("%f", &im[i]);
    }

    for(unsigned char i = 0; i < N; i++)
    {
        printf("s[%d] = %.1f + j*(%.1f)\n", i, re[i], im[i]);
    }

    double sum = 0;
    float max = re[0];
    int index = 0;

    for(unsigned char i = 0; i < N; i++)
    {
        sum += (re[i] * re[i]) + (im[i] * im[i]);

        if(max < re[i])
        {
            max = re[i];
            index = i;
        }
    }

    printf("Sygnal energy: %.1lf\nMax real element: %.1f(index:%d)\n", sum, max, index);

    return 0;
}