#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// For create functions
#include "headers.h"

// Prototype for helper function
char convert(int ascii);

void fileconverter(char infile[20], char outdirectory[20])
{
	FILE *in, *out;
	int c;
	int power = 0;
	int counter = 0;
	int character = 0;
	const int SIZE_OF_RECORD = 29;
	char *record = (char*) malloc(sizeof(char) * SIZE_OF_RECORD);

	// Opens bin file
	in = fopen(infile, "r");

	// Creates file using create.c
	create("-f", outdirectory);
	// Opens out text file
	out = fopen(outdirectory, "w");

	while (c != EOF)
	{
        c=getc(in);
        if (c == '1')
        {
        	power = 7 - ((ftell(in) - 1) % 8); //ftell(first)==1->1000 0000->power=7-(1-1)=7-> 2^7
			character += pow(2.0, (double) power); //adds all 1's to the character
        }
        counter++; //keeps track of bits
		if ((counter % 8) == 0) //after 8 bits -> convert the character and reset
		{
			char append = convert(character);
			strncat(record, &append, 1);
			character = 0;

			if (append == '\n') 
			{
				// Prints record out in text file
				fprintf(out, record);

				// New allocation of memory for record to reset
				record = (char*) malloc(sizeof(char) * SIZE_OF_RECORD);
			}
		}
	}

	free(record);

	// Closes opened files
	fclose(in);
	fclose(out);
}


char convert(int ascii)
{
	char c = ascii; //converts ascii to char and prints
	return c;
}

































