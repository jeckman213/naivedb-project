#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**--------------------------[desired purpose]--------------------------**/


/**--------------------------Structure definition--------------------------**/
// struct definition for the airline structure **/
typedef struct Airline_S{
	char airline[7];
	int occ;
	struct Airline_S *next;
	struct Airline_S *prev;
}Airline_S;

// struct definition for the airport structure **/
typedef struct Airport_S{
	char airport[3];
	struct Airline_S *fltInfo;
	struct Airport_S *next;
	struct Airport_S *prev;
}Airport_S;

// create original global struct and keep records of the head adress
Airport_S *ap = createNewPort();
Airport_S **AP = &ap;
Airline_S *al = createNewLine();
Airline_S **AL = &al;

 //link airport with airline
ap->fltInfo = al;
/**----------------------------------------------------**/


/**--------------------------Create & Allocate space for new/temp nodes --------------------------**/
//create a new airport node 
Airport_S *createNewPort(){
	Airport_S *ap = malloc(sizeof(Airport_S));
	return ap;
};

/** create a new airline node **/
Airline_S *createNewLine(){
	Airline *al = malloc(sizeof(Airline_S));
	return al;
};
/**----------------------------------------------------**/


/**--------------------------Search existing Nodes--------------------------**/
// RETURN the next AIRPORT node 
Airport_S *getNextPort(Airport *ap){
	Aiport_S *temp = createNewPort();
	temp = ap->next;
	return temp;
};
//RETURN next AIRLINE node
Airline_S returnNextPort(Airline_S *al){
	Airline_S *temp = createNewLine();
	temp = al->next;
	return temp;
};
/**----------------------------------------------------**/


/**--------------------------Create and link new additional nodes--------------------------**/
// if there isnt a NEXT node, CREATE one and store information 
void newAirportLinker(char cap[3], char cal[7], Airport_S *ap){
	Aiport_S *temp = createNewPort();
	Airline_S *temp2 = createNewLine();
	ap->next = temp;
	temp->fltInfo = temp2;
	temp->prev = ap;
	temp->airport = cap;
	temp->fltInfo->airline = cal;
	temp->fltInfo->occ = 1;	
};
// CREATE a NEW airline node for an existing airport node and link it to existing list 
void newAirlineLinker(char cal[7], Airport *ap, Airline_S *al){
	Airline_S *temp = createNewLine();
	al->next = temp;
	temp->prev = al;
	temp->airline = cal;
	temp->occ = 1;
};
/**----------------------------------------------------**/

/**--------------------------traverse / build nodes--------------------------**/
//cal = check airline
//cap = check airport
void nodeHandler(char *cal, char *cap, Airport_S *apt) {
	Airport_S *temp = createNewPort();
	Airline_S *tempAl = createNewLine();
	//If the first node's airport name is empty, populate all it's values
	if(ap->airport == ''){
		strcpy(cap,ap->airport);
		strcpy(cal, ap->fltInfo->airLine);
		ap->fltInfo->occ++;
		ap->fltInfo->next = NULL;
		ap->fltInfo->prev = NULL;
		ap->next = NULL;
		ap->prev = NULL;
		return 0; 
	}
	//if airport matches
	else if(strcmp(ap->airport, cap) == 0){
		//and airline file matches
		if(strcmp(ap->fltInfo->airline, cal) == 0){
			apt->fltInfo->occ++; 
			return 0;
		}
		// or airline file doesn't match
		//...loop through the airline nodes 
		else if(strcmp(ap->fltInfo->airline, cal)!= 0 && ap->fltInfo->next!= NULL){
			temp=apt;
			temp->fltInfo = temp->fltInfo->next;
			nodeHandler(cal,cap,temp);
		}
		//if all else fails keep airport and add new airline file/node
		else{
			temp = apt;
			temp->fltInfo->next = nextAl;
			nextAl->occ++;
			strcpy(nextAl->airline, cal);
			nextAl->prev = apt->fltInfo;	
		}
	}
	//airport doesn't match
	else{
		//the next airport doesn't exist so create one
		if(apt->next == NULL){
			apt->next = temp;
			temp->prev = apt;
			strcpy(temp->aiport, cap);
			strcpy(temp->fltInfo->airline, cal);
			temp->fltInfo->occ++;
		}
		else{
			temp = apt->next;
			nodehandler(cal,cap,temp);
		}
	}
}
/**----------------------------------------------------**/


/**--------------------------Loop Through File and get values--------------------------**/
//parse each line of a text file and add records to two layer doubly linked list  
int parse(const char *f, const struct stat *flightD, int type){
	
	//variables to store read values from file
	char need[100],airlineFile[6], chkAirPt[3];
	int i,j,spaces; //Loop and space counter
	spaces = 0;

	
	//open and read file
	FILE *fp = fopen(f, "r");
	
	if(fp==NULL){
		printf("Cannot open file %s, please try again.", f);
	}
	if(type == FTW_F){ //check if filepointer is at a file or something else
		while(fp != EOF){
			fgets(100, need, fp);
			j=0;
			for(i=0;i<101;i++){
					if(spaces == 1 && j < 3){
						chkAirPt[j] ==need[i];
						j++;
					}
					if(need[i] == " "){
						space++;
					}
					if(i<2){
						airlineFile[i] = need[i];
					}
				}
				strcat(airlineFile, ".txt");
				nodeHandler(airlineFile, chkAirPt, ap);
		}
	}
	
	
}
/**----------------------------------------------------**/


/**--------------------------MAIN--------------------------**/
void main(int argc, char *argv[]){
	
	//prototype for parse function
	int parse(const char *, const struct stat *, int)
	
	//test how many arguments are passed in the calling of the function
	//to see if the user submitted a preferred filename
	if(argc == 1){
		ftw(".", parse, 2 );
	}
	else if ( argc == 2){
		ftw(argv[2], parse, 2);
	}
	
	
}
/**----------------------------------------------------**/
