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
 * Function to read string dynamically from the input stream symbol-by-symbol.
 * \param[in] in The input stream
 * \param[out] lastError Error code
 * \return A string from the input
 */
char* ReadLine(FILE* in, error_t* lastError)
{
  char* buffer = NULL;
  char* string = (char*) malloc(sizeof(char));
  int index = 0;
  int tmp = fgetc(in);
  if (tmp == EOF)
  {
    free(string);
    return NULL;
  }
  if (string == NULL) /* checking malloc */
  {
    *lastError = ERR_NOT_ENOUGH_MEMORY;
    while ((tmp = fgetc(in)) != EOF && tmp != '\0' && tmp != '\n')
      return NULL;
  }
  string[index] = (char) tmp;
  while (string[index] != '\0' && string[index] != '\n' && string[index] != EOF)
  {
    buffer = (char*) realloc(string, sizeof(char) * (++index + 1));
    if (buffer == NULL)
    {
      string[index] = '\0';
      free(string);
      tmp = (char) fgetc(in);
      while (tmp != '\n' && tmp != EOF && tmp != '\0')
        tmp = (char) fgetc(in);
      *lastError = ERR_NOT_ENOUGH_MEMORY;
      return NULL;
    }
    else
      string = buffer;
    string[index] = (char) fgetc(in);
  }
  if (string[index] == '\n' || string[index] == EOF)
    string[index] = '\0';
  return string;
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
  }
  if (in != stdin)
    fclose(in);
  return 0;
}