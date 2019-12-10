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

/*	// If the user just enter an empty line display a list of commands that can be done
	if (strcmp(line, "\n")=0)
	{
		printf("List of commands:\n create: flags -f (create file), -d (create directory), -h (create hard link), and -s (create soft link)");
		printf("\n fileconverter [infile] [outdirectory]");
		printf("\n indexer [index file name] [directory]");
		printf("\n srchindx [flag] [search terms separated by ;] [index file name] [path]\n\tFlags: -o (origin airport), -d (destination airport)");
		return 0;
	}
*/	
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
				char *args[]={"./create", flag, filename1, NULL}; //create array of strings used as command line arguments
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

				else             //parent waits for child and continues to take inputs
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
				char* args[5];
				//Get first file name
				strcpy(filename1, strtok(NULL, " "));

                                // Gets second file name
                                strcpy(filename2, strtok(NULL, " "));
				if (filename2!=NULL)
				{
                                	 char* args[]={"./indexer", filename1, filename2, NULL};
				}
				else
				{
					 char* args[]={"./indexer", filename1, NULL};
				}
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

		else if (strcmp(command, "srchindx") == 0)
                {
                        char flag2[3]; //command line arguments for srchindx
			char keywords[50];
			char directory[50];
			char indexerFile[50];
			// Gets the flag
                        strcpy(flag2, strtok(NULL, " "));

                        // Gets the entered search words
                        strcpy(keywords, strtok(NULL, " "));

			strcpy(indexerFile, strtok(NULL, " "));

                        strcpy(directory, strtok(NULL, " "));
			
		        char* args[]={"./srchindx", flag2, keywords, indexerFile, directory, NULL};
                        child=fork();
                        if (child==0)
                        {
                        execv("./srchindx", args);
                        perror("srchindx failed");
                        return EXIT_SUCCESS;
			}
			else if (child==-1)
				return EXIT_FAILURE;
			else
			{
			int status;
			waitpid(child, &status, WNOHANG);
			}
		}
		if (argc > 1) //Reads commands from provided script
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

