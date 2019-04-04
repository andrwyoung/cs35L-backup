#include <stdio.h> //for I/O
#include <stdlib.h> //for qsort, malloc, alloc and free

int unfrob(char a)
{
	return a ^ 42;
}

int frobcmp(const char* a, const char* b)
{
	for(;; a++, b++)
	{
		if(*a == ' ' && *b == ' ') return 0;
		if(*a == ' ' || unfrob(*a) < unfrob(*b)) return -1;
    	if(*b == ' ' || unfrob(*a) > unfrob(*b)) return 1;
	}
}

int cmp(const void* a, const void* b)
{
	return frobcmp(*(const char**)a, *(const char**)b);
}










void dealloc(char** words, int num)
{
	int i = 0;
	while(i < num)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

void errmem(char** words, int num)
{
	dealloc(words, num);
	fprintf(stderr, "ERROR: allocating memory");
	exit(1);
}

void checkerr(char** words, int num)
{
	if(ferror(stdin))
	{
		dealloc(words, num);
		fprintf(stderr, "ERROR: reading from stdin");
		exit(1);
	}
}









int main()
//reads frobincated text lines from stdin
//writes sorted version to standard output
//in frobnicated text lines
{
	

	char** words = (char**) malloc(sizeof(char*)); //hold the words
	int numwords = 0; //number of words inside array
	if(words == NULL) errmem(words, numwords);
	
	//read in first letter from stdin
	char c = getchar();
	checkerr(words, numwords);
	while(c != EOF)
	{
		char* word = (char*) malloc(sizeof(char));
		if(word == NULL) errmem(words, numwords);
		int len = 0;

		//look for single a word
		while(c != ' ' && c != EOF)
		{
			word[len] = c;
			char* temp = realloc(word, (len + 1) * sizeof(char)); //reallocate for next character
			if(temp == NULL) errmem(words, numwords);
			
			word = temp;
			len++;
			
			c = getchar(); //read next character in
			checkerr(words, numwords);
		}
		c = getchar();
		checkerr(words, numwords);

		//add that word into words array
		if(len > 0)
		{	
			word[len] = ' ';
			words[numwords] = word;
			char** temp = realloc(words, (numwords + 2) * sizeof(char*)); //reallocate for next word
			if(temp == NULL) errmem(words, numwords);

			words = temp;
			numwords++;
		}
	}

	//sorting
	qsort(words, numwords, sizeof(char*), cmp);

	//printing sorted words
	int i = 0;
	while(i < numwords)
	{
		int j = 0;
		while(words[i][j] != ' ')
		{
			putchar(words[i][j]);
			j++;
		}
		putchar(' ');
		i++;
	}

	//cleaning up
	dealloc(words, numwords);
	return 0;
}