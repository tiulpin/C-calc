// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma warning(disable:4996) /* disables Compiler Warning (level 3) C4996 to pass tests */
#include "../headers/ProcessLine.h"
/**
 * \file Main.c
 * \author Viktor Tiulpin <viktor@tiulp.in>
 * \version 1.0
 * \section DESCRIPTION
 * Converts math expressions to Reverse-Polish-Notation using Shunting-yard algorithm and evaluates them.
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */

/**
 * Function to read string dynamically from the input stream symbol-by-symbol.
 * \param[in] The input stream
 * \param[out] lastError Error code
 * \return A string from the input
 */
char *ReadLine(FILE *in, error_t *lastError)
{
  char *buffer = NULL;
  char *line = (char *) malloc(sizeof(char));
  int tmp;
  int index = 0;
  tmp = fgetc(in);
  if (tmp == EOF)
  {
    free(line);
    return NULL;
  }
  if (line == NULL) /* checking malloc */
  {
    *lastError = ERR_NOT_ENOUGH_MEMORY;
    while (tmp != '\n')
    {
      tmp = (char) fgetc(in);
      if (tmp == EOF)
      {
        break;
      }
    }
    return NULL;
  }
  line[index] = (char) tmp;
  while (line[index] != '\n' && line[index] != (char) EOF)
  {
    buffer = (char *) realloc(line, sizeof(char) * (++index + 1));
    if (buffer == NULL)
    {
      *lastError = ERR_NOT_ENOUGH_MEMORY;
      tmp = (char) fgetc(in);
      while (tmp != '\n' && tmp != EOF && tmp != '\0')
        tmp = (char) fgetc(in);
      return NULL;
    }
    line = buffer;
    line[index] = (char) fgetc(in);

  }
  if (line[index] == '\n' || line[index] == (char) EOF)
  {
    line[index] = '\0';
  }
  return line;
}
int main(int argc, char const *argv[])
{
  FILE *in = stdin;
  char *line = NULL;
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
  {
    fclose(in);
  }
  return 0;
}