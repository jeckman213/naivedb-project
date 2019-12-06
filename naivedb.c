#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "headers.h"
#include "commands.h"

int main (int argc, char *argv)
{
	char* args[]={"./interfaceFunctions", NULL};

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
		waitpid(child, &status, WNOHANG);
		printf("Exiting NaiveDB. Goodbye!\n");
	}
}
