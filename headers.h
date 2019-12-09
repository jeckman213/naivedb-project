/**--------------------------Structure definition--------------------------**/
// struct definition for the airline structure **/

typedef struct Airlines
{
    // String airline code
	char *filename;

    // Number of occurences of the parent airport
	int occurences;
}Airline;

// struct definition for the airport structure **/
typedef struct Airports
{
    // String airport code
    char *airPortCode;

    // Array of airlines that occur in this airport
	Airline *airLines[20];
}Airport;

// Struct for holding a hash node
typedef struct HashNode
{
    // Hash Value
    int value;

    // The origin airport
    char origin[5];

    // The number of airlines operation from origin airport
    int numOperating;

    // Next node in linked list
    struct HashNode *next;

}HashNode;

extern char* getLine(FILE* stream);

/*Hash Function*/
int  hashFunction(char *s,  int T) {

   /* The parameter s represents the symbol to be hashed and  */
   /* the parameter T represents the size of the hash table.  */
   /* The function returns the hash value for the symbol s.   */

   /* String s is assumed to be terminated with '\0'.         */
   /* It is also assumed that T is at least 2. The returned   */
   /* hash value is an integer in the range 0 to T-1.         */

   /* The function computes the hash value using arithmetic   */
   /* based on powers of the BASE value defined below.        */

   #define  BASE   127

   int h = 0;     /* Will hold the hash value at the end. */
   int temp;      /* Temporary.                           */

   /* The hash value is computed in the for loop below. */
   for (;  *s != 0;  s++) {
       temp = (BASE * h + *s);
       if (temp < 0) temp = -temp;
       h = temp % T;
   }

   /* The hash value computation is complete. So, */
   return h;

} /* End of hash function */

typedef struct node {
struct node *left;
struct node *right;
char key[4];
int occurrences;
}Tree;

//Creates a node for the binary tree
Tree *createNode(char key[4], int occurrences)
{
Tree *node=(Tree*)malloc(sizeof(Tree));
strcpy(node->key, key);
node->occurrences=occurrences;
node->right=NULL;
node->left=NULL;
return(node);
}

void inorderPrint(Tree* node)
{
if(node==NULL)
        return;
inorderPrint(node->left);
printf("%s\t", node->key);
inorderPrint(node->right);
}
