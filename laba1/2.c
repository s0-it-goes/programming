#include <stdio.h>

int main()
{
	float t = 0.0;
	char type = 0;

	printf("Input temperature: ");
	scanf("%f%c", &t, &type);

	switch(type)
	{
		case 'C':
		case 'c':
			t = (t * 9 / 5) + 32;
			type = 'f';
			break;
		case 'F':
		case 'f':
			t = (t - 32) * 5 / 9;
			type = 'c';
			break;
		default:
			printf("Output error");
			return 0;
	}

	printf("\nOutput temperature: %.1f%c\n", t, type);


	return 0;
}
