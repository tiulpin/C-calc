// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../headers/Calculate.h"
#include "../headers/Operations.h"
double sum(double left, double right)
{
  return (left + right);
}
double sub(double left, double right)
{
  return (left - right);
}
double mul(double left, double right)
{
  return (left * right);
}
double din(double left, double right)
{
  return (left / right);
}
double neg(double only)
{
  return -only;
}
double pos(double only)
{
  return only;
}
double ctg(double only)
{
  return (cos(only) / sin(only));
}
double Calculate(node_t node, error_t *lastError)
{
  if (*lastError == ERR_OK)
  {
    switch (node->type_)
    {
    case NUM:
    {
      if (isinf(node->number_) || isnan(node->number_))
      {
        *lastError = ERR_INF_NAN;
      }
      return node->number_;
    }
    case B_OP:
      return BOPS[node->bin_](Calculate(node->left, lastError), Calculate(node->right, lastError));
    case U_OP:
      return UOPS[node->un_](Calculate(node->only, lastError));
    default:
      *lastError = ERR_WRONG_EXPRESSION;
    }
  }
  return NAN;
}