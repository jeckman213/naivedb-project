#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"

int main (int argc, char *argv)
{
char command[100], flag[10], string[100]; //May have to change to malloc later
//string = name of new file for create command
printf("Enter a command (format is [command] [flag] [string]): ");
scanf("%s %s %s", command, flag, string);//Might need to account for file names with spaces

if (strcmp(command, "create")==0)
	create(flag, string);
return 0;
}
