#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

// Helper function prototype
bool fileExists(char filename[20]);

int create(char flag[10], char filename[20]) //May have to update with malloc later
{
  FILE *fp;

  //-f = filepath, permission 0640
  // -d = directory path, permission 0750
  //-h = hardlink
  //-s = softlink

  if (strcmp(flag, "-f")==0)
  {
	// Checks to see if a file with that name already exists
	if (fileExists(filename))
	{
		printf("ERROR: File with name '%s' already exists\n", filename);
		return -1;
	}

	// Creates and opens file
	fp = fopen(filename, "w+"); //creates a file with the given name

	// Closes file
	fclose(fp);

	// Checks whether the file exists now
	if (fileExists(filename))
	{
	  printf("File Created\n");
	  return 0;
	}
	else
	{
	  printf("ERROR: File not create\n");
	  return -1;
	}
	  
  }
  else if (strcmp (flag, "-d")==0)
  {
	// First checks if there is a directory already with the inputed name
	if(!fileExists(filename))
	{
		int dirCreated = mkdir(filename, 0700);
	
		if (!dirCreated)
			return 0;
		else
			return -1;
	}
	else
	{
		printf("ERROR: Directory with name '%s' already exists\n", filename);
	}
  }
 /* 
  *else if (strcmp (flag, "-h")==0)
  *	//do something
  *else if(strcmp (flag, "-s")==0)
  *	//do something
  */
  else
  {
	printf("Error, flag %s not found.", flag);
	return -1;
  }
	/* Change permissions with chmod to 0640, can be done with exec() and fork and stuff */

	return 0;

}

// Helper function for checking whether a file already exists or not in the current directory
bool fileExists(char filename[20])
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);

}
