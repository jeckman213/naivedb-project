#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>

// Helper function prototype
bool fileExists(char filename[20]);

int create(char flag[3], char filename[20])
{
  FILE *fp;

  //-f = filepath, permission 0640
  // -d = directory path, permission 0750
  
  if (strcmp(flag, "-f") == 0)
  {
	fp = fopen(filename, "w+"); //creates a file with the given name

	// Checks whether the file exists now
	if (fileExists(filename))
	  return 0;
	else
	  return -1;
  }
  else if (strcmp (flag, "-d") == 0)
  {
	// First checks if there is a directory already with the inputed name
	if(!fileExists(filename))
	{
		int dirCreated = mkdir(filename, 0750);
	
		if (!dirCreated)
			printf("Directory Created\n");
		else
			printf("Failed to create directory\n");
	}
	else
		printf("Directory with that name already exists\n");
  }
  else
  {
	printf("Error, flag %s not found.", flag);
	return -1;
  }
	/* Change permissions with chmod to 0640, can be done with exec() and fork and stuff */

	return 0;

}

// Creates hard or soft links between two files depending on specified flag
int createLinks(char flag[3], char oldFileName[20], char newFileName[20])
{
	if (strcmp(flag, "-h") == 0)
	{
		int linked = link(oldFileName, newFileName);

		if (linked == 0)
		{
			printf("Hard Link Created\n");
			return 0;
		}
		else 
		{
			printf("ERROR: Hard link failed to link the two files\n");
			return -1;
		}
	}
	else if (strcmp(flag, "-s") == 0)
	{
		int linked = symlink(oldFileName, newFileName);

		if (linked == 0)
		{
			printf("Soft Link Created\n");
			return 0;
		}
		else 
		{
			printf("ERROR: Soft linked failed to link the two files\n");
			return -1;
		}

	}
	else 
	{
		printf("ERROR: Something went wrong in CreateLinks()\n");
		return -1;
	}

}

// Helper function for checking whether a file already exists or not in the current directory
bool fileExists(char filename[20])
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);

}
