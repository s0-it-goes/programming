#include <stdio.h>
#include <unistd.h>
int main()
{

        for(int i = 1; i < 10000000; i++)
        {
		printf("\x1b[2J\x1b[H\n\n");
		switch(i % 10)
		{
			case 0:
				for(int k = 0; k < 10; k++)
				{
					printf("%35c**********\n", ' ');
				}
				break;
			case 1:
			case 9:
				for(int k = 0; k < 10; k++)
				{
					printf("%36c********\n", ' ');
				}
				break;
			case 2:
			case 8:
				for(int k = 0; k < 10; k++)
				{
					printf("%37c", ' ');
					printf("******\n");
				}
				break;
			case 3:
			case 7:
				for(int k = 0; k < 10; k++)
				{
					printf("%38c", ' ');
					printf("****\n");
				}
				break;
			case 4:
			case 6:
				for(int k = 0; k < 10; k++)
				{
					printf("%39c", ' ');
					printf("**\n");
				}
				break;
			case 5:
				for(int k = 0; k < 10; k++)
				{
					printf("%40c", ' ');
					printf("*\n");
				}
				break;
		};

		fflush(stdout);
		usleep(45000);
        }

        return 0;
}

