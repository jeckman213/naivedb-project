#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commands.h"

int main (int argc, char **argv)
{
	pid_t child;
	char command[10],
	       	flag[3],
	       	filename1[20],
		filename2[20];
	char *line = (char*) malloc(sizeof(char) * 50);

	FILE *script;

	//string = name of new file for create command
	printf("Enter a command (format is [command] [flag] [string])\n");

	if (argc > 1)
	{
		script = fopen(argv[1], "r");

		fgets(line, 50, script);
		printf("%s\n", line);
	}
	else
	{
	// Get user input
	scanf("%[^\n]%*c", line);
	}

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
				char *args[]={"./create", flag, filename1, NULL};
				child = fork();
				if (child==0)
					{
	                                execv("./create", args);
        	                        perror("exec failed!");
					return EXIT_SUCCESS;
					}
				else if (child == -1)
				{
					return EXIT_FAILURE;
				}	

				else
				{
					int status;
					waitpid(child, &status, WNOHANG);
					printf("Enter a command (format is [command] [flag] [string])\n");
				}
			}
			// If flag is for creating a hard or soft link
			else if (strcmp(flag, "-h") == 0 || strcmp(flag, "-s") == 0) 
			{	
				// Gets file original file name
				strcpy(filename1, strtok(NULL, " "));
				
				// Gets new file name
				strcpy(filename2, strtok(NULL, " "));

				char* args[]={"./create", flag, filename1, filename2, NULL};

				child = fork();
                                if (child==0)
                                        {
                                        execv("./create", args);
                                        perror("exec failed!");
                                        return EXIT_SUCCESS;
					}
                                else if (child == -1)
                                {
					 return EXIT_FAILURE;
                                }       

                                else
                                {
                                        int status;
                                        waitpid(0, &status, 0);
                                        printf("Enter a command (format is [command] [flag] [string])\n");
				}
			}
			// If an incorrect flag was given
			else 
			{
				printf("ERROR: Flag %s is not a correct flag\n", flag);
			}

	}

		else if (strcmp(command, CONVERT) == 0)
		{
			// Gets the in file name
			strcpy(filename1, strtok(NULL, " "));

			// Gets the out file name
			strcpy(filename2, strtok(NULL, " "));
			char* args[]={"./fileconverter", filename1, filename2, NULL};
			child=fork();
			if (child==0)
			{
			execv("./fileconverter", args);
			perror("fileconverter failed");
			return EXIT_SUCCESS;
			}
			else if (child==-1)
			return EXIT_FAILURE;
			else 
			{
			int status;
                        waitpid(0, &status, 0);
			}
		}
		
		else if (strcmp(command, INDEXER) == 0)
		{
				//Get first file name
				strcpy(filename1, strtok(NULL, " "));

                                // Gets new file name
                                strcpy(filename2, strtok(NULL, " "));

                                char* args[]={"./indexer", filename1, filename2, NULL};

                                child = fork();
                                if (child==0)
                                        {
                                        execv("./indexer", args);
                                        perror("exec failed!");
                                        return EXIT_SUCCESS;
                                        }
                                else if (child == -1)
                                {
                                         return EXIT_FAILURE;
                                }       
				else
				{
				int status;
				waitpid(child, &status, WNOHANG);
				}

		} 
		if (argc > 1)
		{
			if(fgets(line, 50, script) == NULL)
			{
				fclose(script);
				free(line);
				printf("End of script...");
				return 0;
			}
			printf("%s\n", line);
		}
		else 
		{
		// Gets another user input
		printf("Enter another command (enter 'quit' to stop): \n");
		scanf("%[^\n]%*c", line);
		}

		// Inserts first user typed word into command string
		strcpy(command, strtok(line, " "));


	}


return 0;
}

