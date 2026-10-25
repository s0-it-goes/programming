#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char **countLetter(char *text, unsigned short size)
{
    char **letters = (char **) malloc(3 * sizeof(*letters));

    if(letters == NULL)
    {
        return 0;
    }

    for(unsigned short i = 0; i < 3; i++)
    {
        letters[i] = (char *) malloc(2 * sizeof(letters[i])); 
        
        if(letters[i] == NULL)
            return 0;

        letters[i][0] = text[0];
        letters[i][1] = 0;
    }

    unsigned short cnt = 1;

    for(unsigned short i = 0; i < size - 1; i++)
    {
        if(i != 0)
        {
            
        }

        if(isspace(text[i]))
                continue;
        for(unsigned short j = i + 1; j < size; j++)
        {
            if(text[i] == text[j])
                cnt++;
        }
        
        for(unsigned char k = 0; k < 3; k++)
        {
            if(cnt > (letters[k][1]))
            {
                letters[k][0] = text[i];
                letters[k][1] = cnt;
                break;
            }


        }

        cnt = 1;
    }

    return letters;
}

int main()
{
    char text[] = "the quick brown fox jumps over the lazy dog";
    unsigned short size = strlen(text);

    char **letters = countLetter(text, size);

    for(unsigned char i = 0; i < 3; i++)
    {
        printf("буква %c повторилась %d раз\n", letters[i][0], letters[i][1]);
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