#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "headers.h"

// Creates a new hash node for hashtable
HashNode *CreateHashNode()
{
	HashNode *node = malloc(sizeof(HashNode));
	
	node->numOperating = 0;
	
	node->next = NULL;
}

void initHashTable(HashNode *HashTable[])
{
	int i;
	for (i = 0; i < 200; i++)
	{
		HashTable[i] = CreateHashNode();
	}
}

void main(int argc, char** argv)
{
  HashNode *HashTable[200];
  
  initHashTable(HashTable);
  
  char flag[4],
	   *terms[10],
	   filename[20],
	   path[50],
	   currentLine[50],
	   allRecords[50] = "",
	   tempPath[20];
	   
  char *tempTerm = malloc(5),
	   *allTerms = malloc(100),
	   *currentRecord = malloc(10);
	   
  const int ORIGIN_SPACES = 1,
			DEST_SPACES = 2;

  strcpy(flag, argv[1]);

  // If all args are inputed
  if (argc < 5)
  {
    strcpy(filename, "invind.txt");
    strcpy(path, argv[3]);
  }
  else
  {
    strcpy(filename, argv[3]);
    strcpy(path, argv[4]);
  }
  
  // Copy terms seperated by ';' into char array
  strcpy(allTerms, argv[2]);
  
  // Keeps count
  int i = 0, j = 0;
  
  // Total number of terms in array
  int numTerms = 0;
  
  // Gets all terms by looping through all chars in colon seperated list
  for (i = 0; i <= strlen(allTerms); i++)
  {
	  if (allTerms[i] == ':' || i == strlen(allTerms))
	  {
		  terms[numTerms] = malloc(5);
		  strcpy(terms[numTerms], tempTerm);
		  j = 0;
		  numTerms++;
	  }
	  else
	  {
		  tempTerm[j] = allTerms[i];
		  j++;
	  }
  }
  
  // Free unneccessary temp heap memory
  free(tempTerm);
  
  FILE *currentFile = fopen(filename, "r");
  FILE *searchFile;

  // Loops through all terms specified
  int count;
  for(count = 0; count < numTerms; count++)
  {
    printf("...Searching: %s\n", terms[count]);

	// Search all lines in inverted index for terms[count](current term)
    while(fgets(currentLine, 4, currentFile) != NULL)
    {
	  // If a match is found set copy and records into allRecords variable
      if (strcmp(currentLine, terms[count]) == 0) 
      {
		// Skips the end and null terminator
        fgets(currentLine, 50, currentFile);
		// inserts all the records into the variable
		fgets(allRecords, 50, currentFile);
        break;
      }
	  // match isn't found skip next line
      else
        fgets(currentLine, 50, currentFile);
    }

    // If no records were found continue
    if (strcmp(allRecords, "") == 0)
    {
      printf("No records were found for term %s\n", terms[count]);
      continue;
    }
	else 
	  printf("Found Records: %s\n", allRecords);

    // Gets singular records/text files to search in
    currentRecord = strtok(allRecords, " ");
	
	// Removes '(' character from record e.g. (AA.txt -> AA.txt
    currentRecord[0] = '\n';
    currentRecord++;
	
	memset(currentLine, 0, 50);
	
    while(currentRecord != NULL)
    {
	  // Create path to file using args and currentRecord
	  strcpy(tempPath, path);
	  strcat(tempPath, "/");
	  strcat(tempPath, currentRecord);
	  
	  // Open file with path created (e.g AA.txt)
	  printf("...Opening: %s\n", tempPath);
	  searchFile = fopen(tempPath, "r");
	  
	  //airport is origin
      if (strcmp(flag, "-o") == 0)
      {
		int spaces = 0, letterNum = 0;
		char origin[10];
		
		while(fgets(currentLine, 50,searchFile) != NULL)
		{
			// Loop through line to get origin airport code
			for(i = 0; i < strlen(currentLine); i++)
			{
				if(currentLine[i] == ' ')
					spaces++;
				else if (spaces == ORIGIN_SPACES)
				{
					origin[letterNum] = currentLine[i];
					letterNum++;
				}
				
				if(spaces > ORIGIN_SPACES)
					break;
			}
			
			if (strcmp(terms[count], origin) == 0)
			{
				// Insert into Hash
				printf("Found Origin: %s\n", origin);
				
				// Get hash value from hash function
				int hashValue = hashFunction(origin, 200);
				
				HashNode *temp = HashTable[hashValue];
				
				while(1)
				{
					if (temp->numOperating == 0)
					{
						strcpy(temp->origin, origin);
						temp->numOperating += 1;
						break;
					}
					else if(strcmp(temp->origin, origin) == 0)
					{
						temp->numOperating += 1;	
						break;
					}
					else if(temp->next == NULL)
					{
						temp->next = CreateHashNode();
						
						strcpy(temp->next->origin, origin);
						temp->next->numOperating += 1;
						break;
					}
					
					temp = temp->next;
				}
				
				printf("after: temp->origin: %s\t temp->numOperating: %d\n", temp->origin, temp->numOperating);
			}
			
			// Reset spaces and letterNum
			spaces = 0;
			letterNum = 0;
			memset(origin, 0 , strlen(origin));
		}
      }
	  //airport is destination
      else if (strcmp(flag, "-d") == 0)
      {
		Tree *root=NULL, *newNode, *currentNode;//Initiallizes a root node, node to be created, and placeholder node for traversing the tree
		int spaces = 0, letterNum = 0, occurrences;//Number of spaces identifies the destination column in data file
		char dest[10], airline[5];
		memset(dest, 0, sizeof(dest));
		while(fgets(currentLine, 50, searchFile) != NULL)//Searches file for destinations
		{
			for(i = 0; i < strlen(currentLine); i++)
			{
				if(currentLine[i] == ' ')
					spaces++;
				else if (spaces == DEST_SPACES)
				{
					dest[letterNum] = currentLine[i];
					letterNum++;
				}
				else if (spaces==0)
					{
					if (currentLine[i] >= '0' && currentLine[i]<= '9')
						continue;
					else
						airline[i]=currentLine[i]; //Gets airline going to given destination
					printf("Airline: %s\n", airline);
					}

				else if(spaces > DEST_SPACES)//File traversal over
					break;
			}			
			
			spaces=0;
			letterNum=0;

			occurrences=1;//Initialize occurrences
			printf("terms: %s, dest: %s\n", terms[count], dest);
		
			if (strcmp(terms[count], dest) == 0)
			{

				// Insert into Binary Tree
				if (root!=NULL) //Creates the root if none exists
				{
					newNode = createNode(airline, occurrences);
				}
				else // if root exists, creates a node to be added
				{
					root = createNode(airline, occurrences);
				}
				currentNode=root;
				while(currentNode!=NULL)//cycles through tree
					{
					//printf("current node occ: %d\n", currentNode->occurrences);

					if(strcmp(currentNode->key, airline)==0)
						{
						currentNode->occurrences++;//if the airline already exist, occurrences increase
						break;
						}
					else if(currentNode->left==NULL && strcmp(currentNode->key, newNode->key)>0)
						currentNode->left=newNode; 
					else if (currentNode->right==NULL && strcmp(currentNode->key, newNode->key)<0)
						currentNode->right=newNode;
					else if(currentNode->left!=NULL && strcmp(currentNode->key, newNode->key)>0)
						currentNode=currentNode->left;
					else
						currentNode=currentNode->right;
	
					}
			
				}

				printf("Found Destination: %s\n", dest);
		}
			
		printf("Inorder print of tree with destination %s: ", terms[count]);
	        inorderPrint(root);
		printf("\n");
		}
      else
        printf("Flag does not exist\n");
	
		// Close file
		fclose(searchFile);

	   // Update currentRecord with next file
       currentRecord = strtok(NULL, " ");
	   if (strtok(NULL, " ") == NULL)
	     break;
	   else
	   {
	     currentRecord[0] = '\0';
	     currentRecord++;
		 printf("%s\n", currentRecord);
	   }
	    
		// Reset set tempPath to empty
		memset(tempPath, 0 , 20);
    }
	memset(tempPath, 0, 20);
	memset(currentRecord, 0, 5);
	memset(allRecords, 0, 50);
	memset(currentLine, 0, 50);
	
	rewind(currentFile);
	exit(0);
  }

  HashNode *loop;
  int t;
  for(t = 0; t < 200; t++)
  {
    if(HashTable[t]->numOperating != 0)
    {
		printf("Index %d:", t);
		loop = HashTable[t];
        while(1)
		{
			printf("Origin:%s Operating Airlines:%d ->", t, loop->origin, loop->numOperating);
			break;
		}
		printf("\n");
     }
  }

  free(loop);

  // Close inverted index file
  fclose(currentFile);

  return;
}

