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

	// If the user just enter an empty line display a list of commands that can be done
	if (strcmp(line, "\n") == 0)
		printf("List of commands:\n create: flags -f (create file), -d (create directory), -h (create hard link), and -s (create soft link)");

	// Get the command from the entered line
	strcpy(command, strtok(line, " "));

	// Keeps the program running until user types in QUIT command(see commands.h)
	while(strcmp(command, QUIT) != 0)
	{
		// Handles commands
		// If command specified is the create command
		if (strcmp(command, CREATE) == 0)
		{
			strcpy(flag, strtok(NULL, " "));
			
			// if flag is for creating a file or directory
			if (strcmp(flag, "-f") == 0 || strcmp(flag, "-d") == 0)
			{
				strcpy(filename1, strtok(NULL, " "));
				create(flag, filename1);
			}
			// If flag is for creating a hard or soft link
			else if (strcmp(flag, "-h") == 0 || strcmp(flag, "-s") == 0) 
			{	
				// Gets file original file name
				strcpy(filename1, strtok(NULL, " "));
				
				// Gets new file name
				strcpy(filename2, strtok(NULL, " "));

				createLinks(flag, filename1, filename2);
			}
			// If an incorrect flag was given
			else 
			{
				printf("ERROR: Flag %s is not a correct flag\n", flag);
			}
		}
		// If command specified is the fileconverter command
		else if (strcmp(command, CONVERT) == 0)
		{
			// Gets the in file name
			strcpy(filename1, strtok(NULL, " "));

			// Gets the out file name
			strcpy(filename2, strtok(NULL, " "));

			fileconverter(filename1, filename2);			
		}

		// Gets another user input
		printf("Enter another command (enter 'quit' to stop): \n");
		scanf("%[^\n]%*c", line);

		// Inserts first user typed word into command string
		strcpy(command, strtok(line, " "));

	}

	return 0;
}
