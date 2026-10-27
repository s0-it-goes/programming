#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


char **countSymbols(char *text, unsigned short size)
{
    // выделяем память под массив указателей на строки
    char **letters = (char **) malloc(size * sizeof(*letters));

    if(letters == NULL)
        return 0;

    for(unsigned short i = 0; i < size; i++)
    {
        // выделяю память для 2-х элементов в каждой строке
        letters[i] = (char *) malloc(2 * sizeof(char)); 
        
        if(letters[i] == NULL)
        {
            free(letters);
            letters = NULL;

            return 0;
        }
    }

    unsigned char cnt = 1;

    for(unsigned short i = 0; i < size - 1; i++)
    {
        for(unsigned short j = i + 1; j < size; j++)
        {
            if(tolower(text[i]) == tolower(text[j]))
                cnt++;
        }
        
        letters[i][0] = text[i];
        letters[i][1] = cnt;

        cnt = 1;
    }

    letters[size-1][0] = text[size-1]; // т.к. проход во внешнем цикле идёт до size-1, то нужно записать последний элемент
    letters[size-1][1] = 1;

    // удаляем дубликаты
    for(unsigned short i = 0; i < size - 1; i++)
    {
        if(isspace(letters[i][0]) || !isalpha(letters[i][0]))
        {
            letters[i][0] = ' ';
            continue;
        }

        for(unsigned short j = i+1; j < size; j++)
        {
            
            if(tolower(letters[i][0]) == tolower(letters[j][0]))
                letters[j][0] = ' '; // заменяем дубликат на пробел, чтобы было легче отсеивать
        }

    }

    return letters;
}

char **countLetters(char **letters, unsigned short size, unsigned char howMany)
{
    char **counted = (char **) malloc(howMany * sizeof(char *));

    if(counted == NULL)
        return 0;
    
    for(unsigned char i = 0; i < howMany; i++)
    {
        counted[i] = (char *) malloc(2 * sizeof(char));

        if(counted[i] == NULL)
        {
            free(counted);
            counted = NULL;

            return 0;
        }

        counted[i][0] = ' ';
        counted[i][1] = 0;
    }

    for(unsigned short i = 0; i < size; i++)
    {
        if(letters[i][0] == ' ')
            continue;


        for(unsigned char k = 0; k < howMany; k++)
        {
            if(letters[i][0] == counted[k][0])
                break;

            if(letters[i][1] > counted[k][1])
            {
                for(int m = howMany-1; m > k; m--)
                {
                    counted[m][0] = counted[m - 1][0];
                    counted[m][1] = counted[m - 1][1];
                }

                counted[k][0] = letters[i][0];
                counted[k][1] = letters[i][1];

                break;
            } else if(letters[i][1] == counted[k][1])
            {
                if(letters[i][0] < counted[k][0])
                {
                    for(int m = howMany-1; m > k; m--)
                    {
                        counted[m][0] = counted[m - 1][0];
                        counted[m][1] = counted[m - 1][1];
                    }
                    counted[k][0] = letters[i][0];
                    counted[k][1] = letters[i][1];
                    break;
                }
            }
        }
    }

    return counted;
}


int main()
{
    char text[] = "the quick brown fox jumps over the lazy dog";
    unsigned short size = strlen(text);

    char **letters = countSymbols(text, size);

    char **counted = countLetters(letters, size, 5);
    /*
    for(unsigned char i = 0; i < size; i++)
    {
        printf("letters[%d][0]: %c %d\n", i, letters[i][0], letters[i][1]);
    }
    */
    for(unsigned char i = 0; i < 5; i++)
    {
        printf("counted[%d][0]: %c %d\n", i, counted[i][0], counted[i][1]);
    }
    

    for(unsigned char i = 0; i < 3; i++)
    {
        free(letters[i]);
        letters[i] = NULL;
    }

    free(letters);
    letters = NULL;

    return 0;
}