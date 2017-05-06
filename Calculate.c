#include "Calculate.h"
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
  return (1 / tan(only));
}
double Calculate(node_t node)
{
  double (* UOPS[])(double) = {
      neg, pos, sqrt,
      sin, cos, tan,
      ctg, asin, acos,
      atan, log, floor,
      ceil
  };
  double (* BOPS[])(double, double) = {
      pow,
      mul,
      din,
      sum,
      sub
  };
  if (node->type_ == NUM)
    return node->number_;
  if (node->type_ == B_OP)
    return BOPS[node->bin_ - 1](Calculate(node->left), Calculate(node->right));
  else if (node->type_ == U_OP)
    return UOPS[node->un_ - 1](Calculate(node->only));
  return NAN;
}