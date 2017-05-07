#include "Interface.h"
#include "Calculate.h"
#include "SortStation.h"
const char const* error_list[] = {
    "OK",
    "NOT ENOUGH MEMORY",
    "WRONG EXPRESSION",
    "INVALID_OP_PROCESSING",
    "CHECK BRACKETS",
    "INVALID BINARY OPERATION",
    "WRONG NUMBER",
    "INF/NAN",
    "INCORRECT CONVERT",
    "INVALID UNARY OPERATION",
    "INCORRECT SCIENTIFIC NOTATION",
};
error_t ReportError(error_t error)
{
  printf("ERROR: %s\n", error_list[error]);
  return error;
}
int IsOperator(char op)
{
  return op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || isalpha(op);
}
char* Normalize(char* line)
{
  char* copy = (char*) malloc(strlen(line) + 1);
  if (copy == NULL)
  {
    return NULL;
  }
  int index;
  for (index = 0; line[index] != 0; index++)
    copy[index] = (char) tolower(line[index]);
  copy[index] = 0;
  return copy;
}
//TODO: do it again!
//////////////////////////////////////////////////////////
char* ReadLine(FILE* in, error_t* lastError)
{
  char* buffer = NULL;
  char* line = (char*) malloc(sizeof(char));
  if (line == NULL)
  {
    *lastError = ERR_NOT_ENOUGH_MEMORY;
    return NULL;
  }
  int i = 0;
  line[i] = (char) fgetc(in);
  if (line[i] == EOF)
  {
    free(line);
    return NULL;
  }
  while ((line[i] != '\n'))
  {
    if (line[i] == EOF)
    {
      break;
    }
    i++;
    buffer = (char*) realloc(line, sizeof(char) * (i + 1));
    if (buffer == NULL)
    {
      line[i] = '\0';
      *lastError = ERR_NOT_ENOUGH_MEMORY;
      return line;
    }
    else
    {
      line = buffer;
    }
    line[i] = (char) fgetc(in);
  }
  line[i] = '\0';
  return line;
}
//////////////////////////////////////////////////////////
void ProcessLine(char* line, error_t* lastError)
{
  int i;
  double result = 0;
  node_t expression = NULL;
  for (i = 0; line[i] != 0 && isspace(line[i]); i++);
  if ((line[i] == '/' && line[i + 1] == '/') || line[i] == '\0')
  {
    puts(line);
    return;
  }
  printf("%s == ", line);
  line = Normalize(line);
  if (*lastError == ERR_OK)
    expression = Convert(line, lastError);
  if (expression)
  {
    result = Calculate(expression, lastError);
    if (result != result || isinf(result))
      *lastError = ERR_INF_NAN;
    Free(expression);
  }
  else if (*lastError == ERR_OK)
    *lastError = ERR_INCORRECT_CONVERT;
  if (*lastError == ERR_OK)
  {
    if (result == -0)
      result = 0;
    printf("%lg\n", result);
  }
  else
  {
    ReportError(*lastError);
    *lastError = ERR_OK;
  }
}