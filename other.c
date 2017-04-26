//
// Created by tiulpin on 23.04.17.
//
#include "other.h"
#include "calc.h"
const char const* error_list[] = {
    "OK",
    "NOT ENOUGH MEMORY",
    "WRONG EXPRESSION",
    "MEMORY LEAK FOUND",
    "NOT DEFINED",
    "BRACKETS"
};
int IsOperator(char c)
{
  return (c == '+' || c == '-') || (c == '*' || c == '/') || (c == '(' || c == ')') || (c == '^');
}
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
int NeedCalculate(char const* line)
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
void ProcessLine(char const* line, error_t* lastError)
{
  if (!NeedCalculate(line))
  {
    puts(line);
    return;
  }
  printf("%s == ", line);
  double result = Calculate(line, lastError);
  if (*lastError == ERR_OK)
  {
    printf("%lg\n", result);
  }
  else
  {
    ReportError(*lastError);
    *lastError = ERR_OK;
  }
  *lastError = ERR_OK;
}
error_t ReportError(error_t error)
{
  printf("ERROR: %s\n", GetErrorString(error));
  return error;
}
char const* GetErrorString(error_t error)
{
  return error_list[error];
}