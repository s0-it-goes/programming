#include <stdio.h>

int main()
{
	int e = 17, n = 35026003;
	int d = 0, fi = 1;

	for(int p = 1; p < 10000; p += 2)
	{
		for(int q = 1; q < 10000; q += 2)
		{
			if ( p % q )
		}
	}

	for(int p = 0; p < 100; p++)
	{
		for(int q = 0; q < 100; q++)
		{
			fi = (p - 1) * (q - 1);
			/*if ( (d * e) % fi == 1) {
				printf("%d", d);
			}*/
			printf("%d\n", d * e % fi);
		}
	}

	return 0;
}
