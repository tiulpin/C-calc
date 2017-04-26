//
// Created by tiulpin on 23.04.17.
//
#include "calc.h"
const double pi = 3.1415926535897932384626;
const double e = 2.71828182845904523536;
const double eps = 1e-12;
const double EPS = 1e12;
double Sum(double a, double b)
{
  return (a + b);
}
double Sub(double a, double b)
{
  return (a - b);
}
double Mul(double a, double b)
{
  return (a * b);
}
double Div(double a, double b)
{
  return (a / b);
}
double Calculate(char const* expression, error_t* error)
{
  double result;
  char* p_expression = Convert(expression);
  if (*error != ERR_OK)
  {
    return 0.0;
  }
  stack_t* stack = InitializeStack();
  double (* operation)(double, double) = NULL;
  int start;
  int end;
  char* n;
  for (start = 0; p_expression[start = SkipSpaces((char const*) p_expression, start)] != '\0'; start++)
  {
    if (IsOperator(p_expression[start]))
    {
      switch (p_expression[start])
      {
      case '+':
        operation = &Sum;
        break;
      case '-':
        operation = &Sub;
        break;
      case '*':
        operation = &Mul;
        break;
      case '/':
        operation = &Div;
        break;
      case '^':
        operation = &pow;
        break;
      default:
        operation = &Sum;
        break;
      }
      Append(stack, operation(Pop(stack), Pop(stack)));
    }
    else if (isalnum(p_expression[start]))
    {
      n = malloc(sizeof(char));
      end = 0;
      do
      {
        n[end++] = p_expression[start++];
        n = realloc(n, sizeof(char) * (end + 1));
      } while (isalnum(p_expression[start]) || p_expression[start] == '.');
      n[end] = '\0';
      Append(stack, atof((const char*) n));
      free(n);
      start--;
    }
  }
  result = Pop(stack);
  RemoveStack(stack);
  free(p_expression);
  if (result == -0.0 || *error != ERR_OK)
  {
    result = 0.0;
  } //Check errors
  return result;
}