#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
int main(int argc, char const* argv[])
{
  FILE* in = stdin;
  char* line = NULL;
  error_t lastError = ERR_OK;
  // Choose an input source
  if (argc > 1 && (in = fopen(argv[1], "r")) == NULL)
  {
    printf("ERROR: Cannot open file '%s'", argv[1]);
    return -1;
  }
  // Process the data line by line
  while ((line = ReadLine(in, &lastError)) != NULL)
  {
    ProcessLine(line, &lastError);
    free(line);
  }
  // Clean up
  if (in != stdin)
  {
    fclose(in);
  }
  return 0;
}