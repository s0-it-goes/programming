#include <stdio.h>
#include <math.h>

int main()
{
	float x = 0, y = 0;
	float r1 = 1, r2 = 0.5;

	printf("Type x and y coordinates: ");
	scanf("%f %f", &x, &y);

	if(x > 0 && y > 0)
	{
		if( ((pow(x,2) + pow(y,2)) < r1) && (pow(x,2) + pow(y,2) > r2) ) {
			printf("YES");
			return 0;		}

		printf("NO");
		return 0;
	}

	printf("NO");

	return 0;
}
