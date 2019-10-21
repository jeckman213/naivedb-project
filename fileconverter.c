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

//printf("Enter file name");//for manual testing
//scanf("%s", infile);//for manual testing

fp = fopen(infile, "r");

while (c!=EOF)
{
        c=getc(fp); //gets input from a file pointer reading a stream of data, get character then move position indicator
        if (c=='1') //if the unsigned char is showing negative, perfor two's complement
                {
                power=7-((ftell(fp)-1)%8);//ftell(first)==1->1000 0000->power=7-(1-1)=7-> 2^7
		character+=pow(2, power);//adds all 1's to the character
                }
        counter++;//keeps track of bits
	if ((counter%8)==0)//after 8 bits -> convert the character and reset
		{
		convert(character);
		character=0;
		}
}

}


void convert(int ascii)
{
char c = ascii; //converts ascii to char and prints
printf("%c", c);
}

































