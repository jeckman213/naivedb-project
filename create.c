#include <stdio.h>
#include <string.h>

int create(char flag[10], char string[100]) //May have to update with malloc later
{
FILE *fp;

//-f = filepath, permission 0640
// -d = directory path, permission 0750
//-h = hardlink
//-s = softlink

if (strcmp(flag, "-f")==0)
	{
	fp = fopen(string, "w+"); //creates a file with the given name
	if (//fp is true or whatever)
	/*	printf("\nSuccess");
	else
		printf("You messed up idiot lmao");*/
	}
/*
else if (strcmp (flag, "-d")==0)
	//do something
else if (strcmp (flag, "-h")==0)
	//do something
else if(strcmp (flag, "-s")==0)
	//do something
*/
else
	printf("Error, flag %s not found.", flag);
		return -1;
/* Change permissions with chmod to 0640, can be done with exec() and fork and stuff */

return 0;

}
