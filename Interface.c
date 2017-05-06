#include "Interface.h"
#include "Calculate.h"
#include "SortStation.h"
const char const* error_list[] = {
    "OK",
    "NOT ENOUGH MEMORY",
    "WRONG EXPRESSION"
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
int NeedCalculate(char* line)
{
  int i = 0;
  for (i; ((line[i] != '\0') && !(IsOperator(line[i])) && !(isalnum(line[i]))); i++);
  if (line[i] == '\0')
  {
    return 0;
  }
  if (line[i] == '/' && line[i + 1] == '/')
  {
    return 0;
  }
  for (i; line[i] != '\0'; i++)
    if (IsOperator(line[i]) || isalnum(line[i]))
    {
      return 1;
    }
  return 0;
}
char* Normalize(char* line)
{
  char* copy = (char*) malloc(strlen(line) + 1);
  int index;
  for (index = 0; line[index] != 0; index++)
    copy[index] = (char) tolower(line[index]);
  copy[index] = 0;
  return copy;
}
//TODO: do it again!
char* ReadLine(FILE* in, error_t* lastError)
{
  char* buffer = NULL;
  char* line = (char*) malloc(sizeof(char));
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
  if ((NeedCalculate(line)) && (IsOperator(line[i])) && (line[i - 1] != ')'))
  {
    *lastError = ERR_WRONG_EXPRESSION;
  }
  return line;
}
/////////////////////////////////////////////
void ProcessLine(char* line, error_t* lastError)
{
  int i;
  double result = 0;
  for (i = 0; line[i] != 0 && isspace(line[i]); i++);
  if ((line[i] == '/' && line[i + 1] == '/') || line[i] == '\0')
  {
    puts(line);
    return;
  }
  printf("%s == ", line);
  line = Normalize(line);
  node_t expression = Convert(line, lastError);
  if (expression)
  {
    result = Calculate(expression);
    if (result != result || *lastError != ERR_OK || isinf(result))
      *lastError = ERR_WRONG_EXPRESSION;
    Free(expression);
  }
  else
    *lastError = ERR_WRONG_EXPRESSION;
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