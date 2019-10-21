#include <stdio.h>
#include <string.h>
#include <math.h>

int fileconverter(char infile[20], char outdirectory[20])
{
FILE *fp;
int c;
int power=0;
int counter=0;
int character=0;
int format = 0; //counter to know at what char to add space or new line

//printf("Enter file name");//for manual testing
//scanf("%s", infile);//for manual testing

fp = fopen(infile, "r");

while (c!=EOF)
{
        c=getc(fp); //gets input from a file pointer reading a stream of data, get character then move position indicator
        if (c=='1')//if bit is turned on...
                {
		//find out where the bit is in the byte
		//and record that for the power of two
                power=7-((ftell(fp)-1)%8);//ftell(first)==1->1000 0000->power=7-(1-1)=7-> 2^7
		character+=pow(2, power);//adds all 1's to the character -- sums turned on bits in byte
                }
        counter++;//keeps track of bits
	format++; //keeps track of column formation & spacing
	if ((counter%8)==0)//after 8 bits -> convert the character and reset
		{
		convert(character);
		character=0;
		}
	switch(format){
		case 32://when 32 bits are reached print a space
			printf(" ");
			break;
		case 56://when 56 bits are reached print a space
			printf(" ");
			break;
		case 80: //when 80 bits are reached print a space
			printf(" ");
			break;
		case 200://when 200 bits are reached print a new line
			printf("\n");
			format = 0;//reset formatting variable for next line
			break;
		default:
			break;//if all else fails, get out
	}
}

}


void convert(int ascii)
{
char c = ascii; //converts ascii to char and prints
printf("%c", c);
}

































