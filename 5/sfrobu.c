#include <stdio.h> //stderr, stdin
#include <stdlib.h> //for qsort, malloc, alloc and free

#include <sys/types.h> // ssize_t
#include <unistd.h> //STDIN_FILENO STDOUT_FILENO read write

#include <ctype.h> //toupper
#include <limits.h> // CHAR_MIN CHAR_MAX
#include <string.h> //strncmp

int caseon = 1; //just don't want to pass this argument through everything
int unfrob(char a)
{
	a ^= 42;
	if(!(CHAR_MIN <= a && a <= CHAR_MAX) && (a != EOF))
	{
		fprintf(stderr, "Error: Invalid character\n");
		exit(1);
	}
	if(caseon) return toupper(a);
	return a;
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
	fprintf(stderr, "ERROR: allocating memory\n");
	exit(1);
}

void errIO(char** words, int num)
{
	dealloc(words, num);
	fprintf(stderr, "ERROR: reading from stdin\n");
	exit(1);
}









int main(int argc, char* argv[])
//reads frobincated text lines from stdin
//writes sorted version to standard output
//in frobnicated text lines
{
	//checking if "-f" is on
	if(argc != 1)
	{
		if(!strcmp(argv[1], "-f") && argc == 2)
		{
			caseon = 0;
		}
		else
		{
			fprintf(stderr, "Error: invalid arguments\n");
			exit(1);
		}
	}

	char** words = (char**) malloc(sizeof(char*)); //hold the words
	int numwords = 0; //number of words inside array
	if(words == NULL) errmem(words, numwords);
	
	//read in first letter from stdin
	char c;
	ssize_t curr = read(STDIN_FILENO, &c, 1);
	if(curr < 0) errIO(words, numwords);

	while(curr != 0)
	{
		char* word = (char*) malloc(sizeof(char));
		if(word == NULL) errmem(words, numwords);
		int len = 0;


		//look for single a word
		while(c != ' ' && curr != 0)
		{
			word[len] = c;
			char* temp = realloc(word, (len + 1) * sizeof(char)); //reallocate for next character
			if(temp == NULL) errmem(words, numwords);
			
			word = temp;
			len++;
			
			curr = read(STDIN_FILENO, &c, 1); //read next character in
			if(curr < 0) errIO(words, numwords);

		}
		curr = read(STDIN_FILENO, &c, 1);
		if(curr < 0) errIO(words, numwords);



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
	char space = ' ';
	int i = 0;

	while(i < numwords)
	{
		int j = 0;
		while(words[i][j] != ' ')
		{
			
			write(STDOUT_FILENO, &words[i][j], 1);
			j++;
			
		}

		write(STDOUT_FILENO, &space, 1);
		i++;
	}

	//cleaning up
	dealloc(words, numwords);
	return 0;
}