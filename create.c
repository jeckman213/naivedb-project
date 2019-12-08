#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

// Helper function prototype
bool fileExists(char filename[20]);

int main(int argc, char** argv)
{
  FILE *fp;
char flag[3];
char string1[20];
char string2[20];

  strcpy(flag, argv[1]);
  strcpy(string1, argv[2]);
	if (argc>3)
		strcpy(string2, argv[3]);
  //-f = filepath, permission 0640
  // -d = directory path, permission 0750

  if (strcmp(flag, "-f") == 0)
  {
	// Checks to see if a file with that name already exists
	if (fileExists(string1))
	{
		printf("ERROR: File with name '%s' already exists\n", string1);
		return -1;
	}

	// Creates and opens file
	int fd = creat(string1, 0640);
	// Closes file
	close(fd); // closes file opened with file descriptor

	// Checks whether the file exists now
	if (fileExists(string1))
	{
	  printf("File Created\n");
	  return 0;
	}
	else
	{
	  printf("ERROR: File not created\n");
	  return -1;
	}
	  
  }
  else if (strcmp (flag, "-d") == 0)
  {
	// First checks if there is a directory already with the inputed name
	if(!fileExists(string1))
	{
		int dirCreated = mkdir(string1, 0750);
	
		if (!dirCreated)
			return 0;
		else
			return -1;
	}
	else
	{
		printf("ERROR: Directory with name '%s' already exists\n", string1);
	}
  }
// Creates hard or soft links between two files depending on specified flag

  else if (strcmp(flag, "-h") == 0)
	{
		int linked = link(string1, string2);

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
		int linked = symlink(string1, string2);

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
	printf("Error, flag %s not found.", flag);
	return -1;
  }
	

	return 0;

}

// Helper function for checking whether a file already exists or not in the current directory
bool fileExists(char filename[20])
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);

}
