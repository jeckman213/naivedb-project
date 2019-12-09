#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "headers.h"


/**--------------------------Structure Creation--------------------------**/
// Creates a new airline and allocates memory on the heap
Airline *CreateAirline()
{
    // Malloc space for airline struct
    Airline *airline = (Airline*) malloc(sizeof(Airline));

    // Allocate space for airline code string
    airline->filename = (char*) malloc(10);
    strcpy(airline->filename, "empty");

    // Init occurences to 0
    airline->occurences = 0;

    return airline;
}

// Creates a new airport and allocates memory on the heap
Airport *CreateAirport()
{
    // Allocate space for airport struct
    Airport *airport = (Airport*) malloc(sizeof(Airport));

    // Allocate space for airport code string
    airport->airPortCode = (char*) malloc(5);
    strcpy(airport->airPortCode, "empty");

    int count;
    for (count = 0; count < 20; count++)
	    airport->airLines[count] = CreateAirline();

    return airport;
}

    // Airport array for holding all the airports
    Airport *AIRPORTS[50];

// Inserts data into array of airports specified in the params
// Takes in airline file name (ex. AA.txt) and an airport code (ex. JFK)
void InsertData(const char *airlineFileName, char *apCode)
{
    int count = 0,
        inner = 0,
        // Flags for if the values weren't found
        flag = 0;

	// Loop through all airports in airport array
    while (strcmp(AIRPORTS[count]->airPortCode, "empty") != 0)
    {
		// If a match was found with airport code
		if (strcmp(AIRPORTS[count]->airPortCode, apCode) == 0)
        {
            // For each airline in the airport structure
            for (inner = 0; inner <= 10; inner++)
            {
                // If filename(airline file name) matches the airline file name param
                if (strcmp(AIRPORTS[count]->airLines[inner]->filename, airlineFileName) == 0)
                {
                    AIRPORTS[count]->airLines[inner]->occurences++;
					return;
                }
                // If no match was found and the next value in the array is null
                else if (AIRPORTS[count]->airLines[inner]->occurences == 0)
                {
                    // Creation of new airline in array of airlines
                    AIRPORTS[count]->airLines[inner] = CreateAirline();
                    strcpy(AIRPORTS[count]->airLines[inner]->filename, airlineFileName);
                    AIRPORTS[count]->airLines[inner]->occurences++;
                    return;
                }
	       
            }
		// matching values were found
	    flag = 1;
	  }

	count++;
    }
	
	// If no match was found create a new airport and add the airline to it
    if (flag == 0)
    {
        strcpy(AIRPORTS[count]->airPortCode, apCode);
        AIRPORTS[count]->airLines[0] = CreateAirline();
        strcpy(AIRPORTS[count]->airLines[0]->filename, airlineFileName);
        AIRPORTS[count]->airLines[0]->occurences++;
    }
}

int Parse(const char *path, const struct stat *sb, int flag)
{
    // Checks to see if path is flagged as a file
    if (flag == FTW_F)
    {
        // Allocate memory for getting the line/buffer
        char *line = malloc(50);

        // Opens file in read mode
        FILE *file = fopen(path, "r");

        int count = 0,
            spaces = 0;

        char *apCode1 = (char*) malloc(10),
            *apCode2 = (char*) malloc(10);
		
		// Sets all codes and line to empty string
        memset(apCode1, 0, strlen(apCode1));
        memset(apCode2, 0, strlen(apCode2));
        memset(line, 0, strlen(line));

		// Gets a line at a time to read into structure
        while(fgets(line, 50, file) != NULL)
        {
			// For char in line
            for (count = 0; count < strlen(line); count++) 
            {
				// Adds to the spaces counter
                if (line[count] == ' ')
                {
                    // Flag that there was a space indicated
                    spaces++;
                }
				// Gets the first airport code
                else if (spaces == 1)
                {
                    strncat(apCode1, &line[count], 1);
                }
				// Gets the second airport code
                else if (spaces == 2)
                {
                    strncat(apCode2, &line[count], 1);
                }
            }

			// Inserts data into airports array
            InsertData(path, apCode1);
	        InsertData(path, apCode2);

			// Reset the codes and line for reuse in loop and ftw
            memset(apCode1, 0, strlen(apCode1));
            memset(apCode2, 0, strlen(apCode2));
            memset(line, 0, strlen(line));
			
			// Reset spaces for next loop
	        spaces = 0;
        }
		
		// Free all heap memory variables
		free(apCode1);
		free(apCode2);
		free(line);

        // Closes file
        fclose(file);
		return 0;
    }
    // If not flagged as a file throw an error
    else 
    {
        perror("ftw flagged path as something that's not a file");
        return 0;
    }
}

void printToFile(char *filename)
{
    int count = 0,
        inner = 0;

    Airline *temp = CreateAirline();
	Airport *tempAP = CreateAirport();

    FILE *file = fopen(filename, "w");
	
	// Sort airports by alphabet
	while(strcmp(AIRPORTS[count + 1]->airPortCode, "empty") != 0)
    {
		int j;
		for (j = 0; j < 50 - count; j++)
		{
			if (strcmp(AIRPORTS[j + 1]->airPortCode, "empty") == 0) 
				break;
			
			if (AIRPORTS[j]->airPortCode[0] > AIRPORTS[j + 1]->airPortCode[0])
			{
				strcpy(tempAP->airPortCode, AIRPORTS[j + 1]->airPortCode);
				int i;
				for(i = 0; i < 20; i++)
					tempAP->airLines[i] = AIRPORTS[j + 1]->airLines[i];

				strcpy(AIRPORTS[j + 1]->airPortCode, AIRPORTS[j]->airPortCode);
				for(i = 0; i < 20; i++)
					AIRPORTS[j + 1]->airLines[i] = AIRPORTS[j]->airLines[i];

				strcpy(AIRPORTS[j]->airPortCode, tempAP->airPortCode);
				for(i = 0; i < 20; i++)
					AIRPORTS[j]->airLines[i] = tempAP->airLines[i];
			}
		}
		count++;
	}
	
	count = 0;
    
	// Loop through all airports in airports array
    while(strcmp(AIRPORTS[count]->airPortCode, "empty") != 0)
    {
        // Print the airport code
	    fprintf(file, "%s\n", AIRPORTS[count]->airPortCode);

        // Sort by occurences
        while(strcmp(AIRPORTS[count]->airLines[inner]->filename, "empty") != 0)
        {		
            if (AIRPORTS[count]->airLines[inner]->occurences < AIRPORTS[count]->airLines[inner + 1]->occurences)
            {
                    temp->occurences = AIRPORTS[count]->airLines[inner + 1]->occurences;
                    strcpy(temp->filename, AIRPORTS[count]->airLines[inner + 1]->filename);

                    AIRPORTS[count]->airLines[inner + 1]->occurences = AIRPORTS[count]->airLines[inner]->occurences;
                    strcpy(AIRPORTS[count]->airLines[inner + 1]->filename, AIRPORTS[count]->airLines[inner]->filename);

                    AIRPORTS[count]->airLines[inner]->occurences = temp->occurences;
                    strcpy(AIRPORTS[count]->airLines[inner]->filename, temp->filename);
            }
            inner++;
        }

		// Reset inner counter for reuse
        inner = 0;

	    while(strcmp(AIRPORTS[count]->airLines[inner]->filename, "empty") != 0)
	    {
            // Print the file it is in and the number of occurences
	        fprintf(file, "(%s %d) ", 
		        AIRPORTS[count]->airLines[inner]->filename, 
		        AIRPORTS[count]->airLines[inner]->occurences);
            inner++;
	    }

	    fprintf(file, "\n");
		
		// Update count for next iteration
        count++;
		// Reset inner for reuse
        inner = 0;
    } 
	
	// Free temp memory variable
	free(temp);
	
	// Closes file
    fclose(file);
}

void main(int argc, char *argv[])
{
    int count;
    for (count = 0; count < 20; count++)
    {
    	AIRPORTS[count] = CreateAirport();
    }

    /*strcpy(AIRPORTS[0]->airPortCode, "JFK");
   strcpy(AIRPORTS[0]->airLines[0]->filename, "AA.txt");
  AIRPORTS[0]->airLines[0]->occurences++; */

    if (argc == 2)
    {
        ftw(argv[1], Parse, 5);
	    printToFile("invind.txt");
    }
    else 
    {
        ftw(argv[2], Parse, 5);
	    printToFile(argv[1]);
    }
}
