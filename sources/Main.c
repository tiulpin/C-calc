#pragma warning(disable:4996) /* disables Compiler Warning (level 3) C4996 to pass tests */
#include "../headers/ProcessLine.h"
/**
 * \file Main.c
 * \author Viktor Tiulpin <viktor@tiulpin.me>
 * \version 0.9
 * \section DESCRIPTION
 * Converts math expression to Reverse-Polish-Notation using Shunting-yard algorithm and evaluates them.
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
/**
 * Function to read string dynamically from input stream symbol-by-symbol.
 * \param[in] in Input stream
 * \param[out] lastError Error code
 * \return A string from input
 */
char* ReadLine(FILE* in, error_t* lastError)
{
  char* buffer = NULL;
  char* line = (char*) malloc(sizeof(char));
  if (line == NULL) /* checking malloc */
  {
    *lastError = ERR_NOT_ENOUGH_MEMORY;
    return NULL;
  }
  int index = 0;
  line[index] = (char) fgetc(in);
  if (line[index] == EOF)
  {
    free(line);
    return NULL;
  }
  while (line[index] != '\n')
  {
    if (line[index] == EOF)
      break;
    index++;
    buffer = (char*) realloc(line, sizeof(char) * (index + 1));
    if (buffer == NULL)
    {
      line[index] = '\0';
      *lastError = ERR_NOT_ENOUGH_MEMORY;
      free(line);
      return line;
    }
    else
      line = buffer;
    line[index] = (char) fgetc(in);
  }
  line[index] = '\0';
  return line;
}
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
  while ((line = ReadLine(in, &lastError)) != NULL || lastError == ERR_NOT_ENOUGH_MEMORY) /* */
  {
    if (lastError != ERR_OK)
    {
      ReportError(lastError);
      lastError = ERR_OK;
      continue;
    }
    ProcessLine(line, &lastError);
    free(line);
  }
  if (in != stdin)
    fclose(in);
  return 0;
}