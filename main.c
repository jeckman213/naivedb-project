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

	if (strcmp(line, "\n")==0)
		printf("List of commands:\n create: flags -f (create file), -d (create directory), -h (create hard link), and -s (create soft link)");

	// Keeps the program running until user types in QUIT command(see commands.h)
	while(strcmp(line, QUIT) != 0)
	{
		char *token = strtok(line, " ");
		
		int count = 0;
		
		while (token != NULL)
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
			else if (count == 2)
			{
				strcpy(filename1, token);
				count++;
				token = strtok(NULL, " ");
			}
			else
			{
				strcpy(filename2, token);
				token = strtok(NULL, " ");
				break;
			}
		}

		// Handles commands
		if (strcmp(command, CREATE) == 0)
			if (strcmp(flag, "-f") == 0 || strcmp(flag, "-d") == 0)
				create(flag, filename1);
			else
				createLinks(flag, filename1, filename2);

		// Gets another user input
		printf("Enter another command (enter 'quit' to stop): \n");
		scanf("%[^\n]%*c", line);
	}

	return 0;
}
