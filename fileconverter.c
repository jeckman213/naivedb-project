#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

// For create functions
#include "headers.h"

// Prototype for helper function
char convert(int ascii);

// Constants for airlines
const char *AMERICAN = "AA";
const char *DELTA = "DL";
const char *FRANCE = "F";
const char *SKYWEST = "OO";

void fileconverter(char infile[20], char outdirectory[20])
{
	FILE *in, *out;
	int c;
	int power = 0;
	int counter = 0;
	int character = 0;
	const int SIZE_OF_RECORD = 29;
	char *record = (char*) malloc(sizeof(char) * SIZE_OF_RECORD);
	char *path = (char*) malloc(sizeof(char) * 30);

	in = fopen(infile, "r");

	// Creates file using create.c
	create("-d", outdirectory);

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
			printf("Got into append process\n");
			char append = convert(character);
			strncat(record, &append, 1);
			character = 0;

			if (strlen(record) < 3) 
			{
				printf("Got into determine airport\n");
				strncat(path, "/", 1);
				strncat(path, outdirectory, strlen(outdirectory));
				
				printf("Got past first strncat\n");	

				if (strcmp(record, AMERICAN) == 0)
				{
					strncat(path, "/AA.txt", 8);
				}
				else if (strcmp(record, DELTA) == 0)
				{
					strncat(path, "/DL.txt", 8);	
				}
				else if (strcmp(record, FRANCE) == 0)
				{
					strncat(path, "/F.txt", 7);
				}
				else if (strcmp(record, SKYWEST) == 0)
				{
					strncat(path, "/OO.txt", 8);
				} 
				else 
				{
					strncat(path, "/z.txt", 7);
					printf("Didn't find airline code\n");
				}

				printf("%s", path);
				
				creat(path, 0700);
			}

			if (append == '\n') 
			{
				printf("Got to fprintf to txt file\n");
				// Prints record out in text file
				fprintf(out, record);

				// New allocation of memory for record to reset
				record = (char*) malloc(sizeof(char) * SIZE_OF_RECORD);

				// Closes currently opened file
				fclose(out);
			}
		}
	}

	// Closes opened files
	fclose(in);
}


char convert(int ascii)
{
	char c = ascii; //converts ascii to char and prints
	return c;
}

































