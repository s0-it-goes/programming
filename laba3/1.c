#include <stdio.h>

int main()
{
	int n = 1;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%d ", n);
			n += 1;
		}

		printf("\n");
	}

	return 0;
}
