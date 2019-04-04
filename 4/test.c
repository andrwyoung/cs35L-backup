#include <stdio.h>

int main()
{
	char c = getchar();
	while(c != EOF)
	{
		printf("%c\n", c);
		c = getchar();
	}

	return 0;
}