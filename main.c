#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers.h"
#include "commands.h"

int main (int argc, char *argv)
{
	char command[10],
	       	flag[3],
	       	filename1[20],
		filename2[20],
	       	line[100]; //May have to change to malloc later

	//string = name of new file for create command
	printf("Enter a command (format is [command] [flag] [string])\n");

	// Get user input
	scanf("%[^\n]%*c", line);

	command = strtok(line, " ");

	// Keeps the program running until user types in QUIT command(see commands.h)
	while(strcmp(command, QUIT) != 0)
	{
		// Handles commands
		if (strcmp(command, CREATE) == 0)
		{
			flag = strtok(NULL, " ");
			
			if (strcmp(flag, "-f") == 0 || strcmp(flag, "-d") == 0)
			{
				filename1 = strtok(NULL, " ");
				create(flag, filename1);
			}
			else
			{
				filename1 = strtok(NULL, " ");
				filename2 = strtok(NULL, " ");
				createLinks(flag, filename1, filename2);
			}
		}
		else if (strcmp(command, CONVERT) == 0)
		{
					
		}

		// Gets another user input
		scanf("%[^\n]%*c", line);


	}

	return 0;
}
