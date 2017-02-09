#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Include local header files

// TODO: Use all unused parameters and remove this temporary definition
// Helps eliminating warning C4100: 'error': unreferenced formal parameter
#define UNUSED_PARAMETER(name) (void)name

//////////////////////////////////////////////////////////////////////////////
// Dummy calc module

// TODO: Move to a separate module 'calc'
typedef enum
{
  ERR_OK,
  ERR_NOT_ENOUGH_MEMORY,
  // TODO: Add your own error codes
} error_t;

// TODO: Move to a separate module 'calc'
char const* GetErrorString(error_t error)
{
  // TODO: Find the corresponding error description
  UNUSED_PARAMETER(error);
  return "";
}

// TODO: Move to a separate module 'calc'
double Calculate(char const* expression, error_t* error)
{
  double result;

  // TODO: Replace with a computational algorithm subdivided into modules/functions
  UNUSED_PARAMETER(expression);
  result = 4.0;
  if (error != NULL)
    *error = ERR_OK;

  return result;
}

//////////////////////////////////////////////////////////////////////////////
// UI functions

char* ReadLine(FILE* in)
{
  char* line = NULL;
  // TODO: Read a line of text into a dynamic memory block
  UNUSED_PARAMETER(in);
  return line;
}

int NeedCalculate(char const* line)
{
  // TODO: Determine if the line contains an expression
  UNUSED_PARAMETER(line);
  return 1;
}

error_t ReportError(error_t error)
{
  printf("ERROR: %s\n", GetErrorString(error));
  return error;
}

void ProcessLine(char const* line)
{
  error_t lastError = ERR_OK;
  if (!NeedCalculate(line))
  {
    puts(line);
    return;
  }

  printf("%s == ", line);
  double result = Calculate(line, &lastError);
  if (lastError == ERR_OK)
    printf("%lg\n", result);
  else
    ReportError(lastError);
}

int main(int argc, char const* argv[])
{
  FILE* in = stdin;
  char* line = NULL;

  // Choose an input source
  if (argc > 1 && (in = fopen(argv[1], "r")) == NULL)
  {
    printf("ERROR: Cannot open file '%s'", argv[1]);
    return -1;
  }

  // Process the data line by line
  while ((line = ReadLine(in)) != NULL)
  {
    ProcessLine(line);
    free(line);
  }

  // Clean up
  if (in != stdin)
    fclose(in);
  return 0;
}
