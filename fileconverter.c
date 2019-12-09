#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// For create functions
#include "headers.h"
  
// The max size of a record/line of flight data
const int SIZE_OF_RECORD = 30;

int main(int argc, char** argv)
{
  // Files pointers
	FILE *in, *out;
  
  // For converting the binary to a char
	int c;
	int power = 0;
	int counter = 0;
	int character = 0;

//Get infile and outdirectory
	char infile[20];
	char outdirectory[20];
  	strcpy(infile, argv[1]);
	strcpy(outdirectory, argv[2]);

  // For storing the whole flight record/line
	char *record = (char*) malloc(sizeof(char) * SIZE_OF_RECORD);
  
  // For storing the path to the text file in the out directory
	char *path = (char*) malloc(sizeof(char) * 30);
	char *filePath = (char*) malloc(sizeof(char) * 30);

  // Opens binary file in read mode
	in = fopen(infile, "r");

	// Creates basic path to directory (e.g. /OUT_DIRECTORY_NAME)
	strncat(path, outdirectory, strlen(outdirectory));
	strncat(path, "/", 1);
	strcpy(filePath, path);

  // Converts each byte into a char and then inserts it into record
  // After that it fprintf() into a file determined by the first 3 letters of the record
	while (c != EOF)
	{
		c = getc(in);

		if (c == '1')
		{
    		power = 7 - ((ftell(in) - 1) % 8); //ftell(first)==1->1000 0000->power=7-(1-1)=7-> 2^7
			character += pow(2.0, (double) power); //adds all 1's to the character
		}

		counter++; //keeps track of bits
		
		if ((counter % 8) == 0)//after 8 bits -> convert the character and reset
		{
			char append = character;
			printf("%c", append);

			if (strlen(record) < 4 && (append < '0' || append > '9') && append != ' ')
			{
				strncat(filePath, &append, 1);
			}
			strncat(record, &append, 1);
			character = 0;

			if (append == '\n') 
			{
				strncat(filePath, ".txt", 5);
				printf("%s\n", filePath);
				out = fopen(filePath, "a+");

				if (out == NULL)
					printf("Couldn't open/create new file");

				// Prints record out in text file
				fprintf(out, record);

				// New allocation of memory for record to reset
				memset(record, 0, strlen(record));
				memset(filePath, 0 , strlen(filePath));
				printf("hi");
				strcpy(filePath, path);

				// Closes currently opened file
				fclose(out);
			}

		}
	}
  
  // Frees all heap memory
	free(filePath);
	free(record);
	free(path);

	// Closes opened files
	fclose(in);

	return 0;
}
