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

char* getLine(FILE* stream);
