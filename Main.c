#pragma warning(disable:4996)
#include "Interface.h"
int main(int argc, char const* argv[])
{
  FILE* in = stdin;
  char* line = NULL;
  error_t lastError = ERR_OK;
  if (argc > 1 && (in = fopen(argv[1], "r")) == NULL)
  {
    printf("ERROR: Cannot open file '%s'", argv[1]);
    return -1;
  }
  while ((line = ReadLine(in, &lastError)) != NULL)
  {
    ProcessLine(line, &lastError);
    free(line);
  }

  if (in != stdin)
    fclose(in);
  return 0;
}