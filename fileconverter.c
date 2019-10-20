#include <stdio.h>
#include <string.h>
#include <math.h>
#include "headers.h"

// Prototype for helper function
char convert(int ascii);

void fileconverter(char infile[20], char outdirectory[20])
{
	FILE *fp, *out;
	int c;
	int power = 0;
	int counter = 0;
	int character = 0;
	char record = (char*) malloc(sizeof(char) * 28);

	// Opens bin file
	fp = fopen(infile, "r");

	// Creates file using create.c
	create("-f", outdirectory);
	// Opens out text file
	out = fopen(outdirectory, "w");

	while (c != EOF)
	{
        c=getc(fp);
        if (c == '1')
        {
        	power = 7 - ((ftell(fp) - 1) % 8); //ftell(first)==1->1000 0000->power=7-(1-1)=7-> 2^7
			character += pow(2.0, (double) power); //adds all 1's to the character
        }
        counter++; //keeps track of bits
		if ((counter % 8) == 0) //after 8 bits -> convert the character and reset
		{
			strncat(record, convert(character), 1);
			character = 0;
		}

		if (strlen(record) == 28) 
		{
			fprintf(out, record);
			record = (char*) malloc(sizeof(char) * 28);
			return;
		}
	}

	// Closes opened files
	fclose(fp);
	fclose(out);
}


char convert(int ascii)
{
	char c = ascii; //converts ascii to char and prints
	return c;
}

































