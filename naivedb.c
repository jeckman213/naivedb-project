#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "headers.h"
#include "commands.h"

int main (int argc, char **argv)
{
	char *args[4];
	// If a script file is specified make it an arg
	if (argc > 1)
	{
	printf("here\n");
		args[0] = malloc(sizeof(char) * 50);
		strcpy(args[0], "./interfaceFunctions");
		args[1] = malloc(sizeof(char) * 50);
		strcpy(args[1], argv[1]);
		args[2] = NULL;
	}
	// Otherwise don't pass anything
	else 
	{
	printf("here\n");
		strcpy(args[0], "./interfaceFunctions");
		args[1] = NULL;
	}
	printf("1\n");

	printf("Welcome to NaiveDB!\n");

	pid_t child=fork();
	if (child==0)
	{
		execv("./interfaceFunctions", args);
		perror("exec failed");
		return EXIT_SUCCESS;
	}
	else if (child==-1)
		return EXIT_FAILURE;
	else
	{
		int status;
		waitpid(child, &status, 0);
	}
printf("Exiting NaiveDB. Goodbye!\n"); 
return 0;
}
