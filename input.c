#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"

char* getLine(FILE* stream)
{
  char* line = malloc(256);
  fgets(line, sizeof(line), stream);
  return line;
}
