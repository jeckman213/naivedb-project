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
  int fileD = creat(filename, "w+") //use input argument 'filename' to open or create new file descriptor
  if (strcmp(flag, "-f")==0)
  {
	fp = fopen(filename, "w+"); //creates a file with the given name

	// Checks whether the file exists now
	if (fileExists(filename))
	  return 0;
	else
	  return -1;
  }
  else if (strcmp (flag, "-d")==0)
  {
	// First checks if there is a directory already with the inputed name
	if(!fileExists(filename))
	{
		int dirCreated = mkdir(filename, 0700);
	
		if (!dirCreated)
			printf("Directory Created\n");
		else
			printf("Failed to create directory\n");
	}
	else
		printf("Directory with that name already exists\n");
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
