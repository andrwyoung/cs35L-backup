#include <stdio.h> //argc argv getchar putchar
#include <stdlib.h> //exit
#include <string.h> //strlen

void checkerr()
{
	if(ferror(stdin))
	{
		fprintf(stderr, "ERROR: reading from stdin");
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	char* one = argv[1];
	char* two = argv[2];

	//check if there are 2 inputs
	if(argv[3] != NULL && (two == NULL || one == NULL))
	{
		fprintf(stderr, "Error: missing arguments\n");
		exit(1);
	}
	int onelen = strlen(one);
	int twolen = strlen(two);

	//check that lengths are equal
	if(onelen != twolen)
	{
		fprintf(stderr, "Error: arguments must be same length\n");
		exit(1);
	}
	char key[onelen][2];

	//putting it in array now
	int count = 0;
	while(count != onelen)
	{
		if(*one == *two) fprintf(stderr, "Warning: replacing letter\n");
		key[count][0] = *one;
		key[count][1] = *two;

		//duplicates?
		int i = 0;
		while(i < count)
		{
			if(key[i][0] == *one)
			{
				fprintf(stderr, "Error: duplicate letters for input1\n");
				exit(1);
			}
			i++;
		}

		count++;
		one++;
		two++;
	}







	//start reading and replacing
	char c = getchar();
	checkerr();
	while(c != EOF)
	{
		int i = 0;
		while(i < onelen)
		{
			if(c == key[i][0])
			{
				c = key[i][1];
				break;
			}
			i++;
		}
		putchar(c);
		c = getchar();
		checkerr();
	}
	return 0;
}