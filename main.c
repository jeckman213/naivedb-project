#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers.h"
#include "commands.h"

int main (int argc, char *argv)
{
	char command[10],
	       	flag[10],
	       	filename[20],
	       	line[100]; //May have to change to malloc later

	//string = name of new file for create command
	printf("Enter a command (format is [command] [flag] [string])\n");

	// Get user input
	scanf("%[^\n]%*c", line);

	
	// Keeps the program running until user types in QUIT command(see commands.h)
	while(strcmp(line, QUIT) != 0)
	{
		char *token = strtok(line, " ");
		
		int count = 0;
		
		while (token != NULL || count == 3)
		{
			if (count == 0)
			{
				strcpy(command, token);
				count++;
				token = strtok(NULL, " ");
			}
			else if (count == 1)
			{
				strcpy(flag, token);
				count++;
				token = strtok(NULL, " ");
			}
			else 
			{
				strcpy(filename, token);
				break;
			}
		}

		// Handles commands
		if (strcmp(command, CREATE) == 0)
			create(flag, filename);

		// Gets another user input
		scanf("%[^\n]%*c", line);
	}

	return 0;
}
