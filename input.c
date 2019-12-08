#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getLine(FILE* stream)
{
char* line=malloc(256);
fgets(line, sizeof(line), stream);
return line;
}
