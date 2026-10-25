#include <stdio.h>

int main()
{
	int n = 0;
	scanf("%d", &n);

	for(int i = 0; i < n; i++)
	{
		printf("*");

		for(int j = 0; j < n - 2; j++)
		{
			if(i == n - 1 || i == 0)
			{
				printf("*");
				continue;
			}

			printf("-");
		}

		printf("*");
		printf("\n");
	}

	return 0;
}
