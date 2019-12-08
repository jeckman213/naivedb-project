#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "headers.h"

char* main(int argc, char** argv)
{

char* flag[4];
char* terms[100];
char* filename[20];
char* path[50];
char c;
int spacesO=1;
int spacesD=2;
int spaces=0;

strcpy(flag, argv[1]);
strcpy(terms, argv[2]);
strcpy(filename, argv[3]);

if (argc>4)
	strcpy(path, argv[4]);

char* currentTerm = strtok(terms, ";");

while(currentTerm!=NULL)
{

FILE* currentFile=fopen(path, "r");

if (strcmp(flag, "-o")==0) //airport is origin
	{
	c=getchar(path);
	if (c=' ')
		spaces+=1;
	if (spaces==spacesO)
		{
		//get next 3 characters
		if (strcmp(currentTerm, token)
			//found
		}
	}

else if (strcmp(flag, "-d")==0)//airport is destination
	{
	//2 space
	}
else
	printf("Flag does not exist\n");

}

