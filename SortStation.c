#define _USE_MATH_DEFINES
#include "Calculate.h"
#include "Interface.h"
#include "SortStation.h"
int IsUnaryOp(enum Op op)
{
  return (ToBinary_op(op) == B_OP_INVALID && op != OPAR);
}
char* ReadOp(const char* string, int* index, int IsOperation)
{
  int j = 0;
  char* copy = (char*) malloc(sizeof(char));
  if (IsOperation)
  {
    if (string[*index] == '-')
    {
      while (string[*index] == '-')
      {
        copy[j] = string[(*index)++];
        copy = (char*) realloc(copy, sizeof(char) * (++j + 1));
      }
    }
    else
    {
      while (isalpha(string[*index]))
      {
        copy[j] = string[(*index)++];
        copy = (char*) realloc(copy, sizeof(char) * (++j + 1));
      }
    }
  }
  else
    while (isdigit(string[*index]) || string[*index] == '.' || string[*index] == 'e' || string[*index] == '+'
        || string[*index] == '-')
    {
      copy[j] = string[(*index)++];
      copy = (char*) realloc(copy, sizeof(char) * (++j) + 1);
    }
  copy[j] = 0;
  (*index)--;
  return copy;
}
int GetPriority(enum Op op)
{
  return op == OPAR ? -1 :
         op == PLUS || op == MINUS ? 1 :
         op == TIMES || op == DIVIDE ? 2 :
         IsUnaryOp(op) ? 3 :
         op == BEXP ? 4 : -1;
}
int IsOPAR(struct opstack_t* operations)
{
  int i;
  for (i = 0; i < operations->depth_; i++)
    if (operations->elements_[i] == OPAR)
      return 1;
  return 0;
}
enum Binary_op ToBinary_op(enum Op op)
{
  if (op == PLUS)
    return B_OP_PLUS;
  if (op == MINUS)
    return B_OP_MINUS;
  if (op == TIMES)
    return B_OP_TIMES;
  if (op == DIVIDE)
    return B_OP_DIVIDE;
  if (op == BEXP)
    return B_OP_EXP;
  return B_OP_INVALID;
}
enum Unary_op ToUnary_op(enum Op op)
{
  if (op == NEG)
    return U_OP_NEG;
  if (op == POS)
    return U_OP_POS;
  if (op == SQRT)
    return U_OP_SQRT;
  if (op == SIN)
    return U_OP_SIN;
  if (op == COS)
    return U_OP_COS;
  if (op == TAN)
    return U_OP_TAN;
  if (op == CTG)
    return U_OP_CTG;
  if (op == ASIN)
    return U_OP_ASIN;
  if (op == ACOS)
    return U_OP_ACOS;
  if (op == ATAN)
    return U_OP_ATAN;
  if (op == LN)
    return U_OP_LN;
  if (op == FLOOR)
    return U_OP_FLOOR;
  if (op == CEIL)
    return U_OP_CEIL;
  return U_OP_INVALID;
}
enum Op DefineBinaryOp(char op)
{
  if (op == '+')
    return PLUS;
  if (op == '-')
    return MINUS;
  if (op == '*')
    return TIMES;
  if (op == '/')
    return DIVIDE;
  if (op == '^')
    return BEXP;
  return INVALID;
}
enum Op DefineUnaryOp(char* op)
{
  if (*op == '+')
    return POS;
  if (*op == '-')
  {
    if (strlen(op) & 1)
      return NEG;
    return POS;
  }
  if (strcmp(op, "sqrt") == 0)
    return SQRT;
  if (strcmp(op, "sin") == 0)
    return SIN;
  if (strcmp(op, "cos") == 0)
    return COS;
  if (strcmp(op, "tg") == 0)
    return TAN;
  if (strcmp(op, "ctg") == 0)
    return CTG;
  if (strcmp(op, "arcsin") == 0)
    return ASIN;
  if (strcmp(op, "arccos") == 0)
    return ACOS;
  if (strcmp(op, "arctg") == 0)
    return ATAN;
  if (strcmp(op, "ln") == 0)
    return LN;
  if (strcmp(op, "floor") == 0)
    return FLOOR;
  if (strcmp(op, "ceil") == 0)
    return CEIL;
  return INVALID;
}
void Process(struct stack_t* operands, struct opstack_t* operations, error_t* lastError)
{
  enum Op op = INVALID;
  if (operations->depth_ != 0)
    op = Pop_op(operations);
  if ((op == POS || op == NEG || op == SQRT || op == SIN || op == COS || op == TAN || op == CTG || op == ASIN ||
      op == ACOS || op == ATAN || op == LN || op == FLOOR || op == CEIL) && operands->depth_ > 0 && op != INVALID)
  {
    node_t only = Pop(operands);
    node_t new_node = u_op(only, ToUnary_op(op));
    Append(operands, new_node);
  }
  else if (((op == PLUS) || (op == MINUS) || (op == TIMES)
      || (op == DIVIDE) || (op == BEXP)) && operands->depth_ > 1 && op != INVALID)
  {
    node_t right = Pop(operands);
    node_t left = Pop(operands);
    node_t new_node = b_op(left, right, ToBinary_op(op));
    Append(operands, new_node);
  }
  else
    *lastError = ERR_WRONG_EXPRESSION;
}
node_t Convert(const char* string, error_t* lastError)
{
  struct opstack_t* operations = InitOperations();
  struct stack_t* operands = InitOperands();
  int mayunary = 1;
  enum Op cur_op;
  char* copy;
  int index;
  int* indexptr = &index;
  for (index = 0; string[index] != 0 || *lastError != ERR_OK; ++index)
    if (isgraph(string[index]))
    {
      if (string[index] == '(')
      {
        Append_op(operations, OPAR);
        mayunary = 1;
      }
      else if (string[index] == ')')
        if (operands->depth_ && IsOPAR(operations))
        {
          while ((operations->depth_ != 0) && (Back(operations) != OPAR
              || (operations->depth_ > 1) && IsUnaryOp(operations->elements_[operations->depth_ - 2])
                  && Back(operations) == OPAR))
          {
            if ((operations->depth_ > 1) && IsUnaryOp(operations->elements_[operations->depth_ - 2])
                && Back(operations) == OPAR)
              Pop_op(operations);
            Process(operands, operations, lastError);
          }
          if ((operations->depth_ != 0) && Back(operations) == OPAR)
            Pop_op(operations);
          mayunary = 0;
        }
        else
          *lastError = ERR_WRONG_EXPRESSION;
      else if (IsOperator(string[index]))
      {
        if (string[index + 1] != 0 && (string[index] == 'p' && string[index + 1] == 'i'))
        {
          Append(operands, Num(M_PI));
          index++;
          mayunary = 0;
          continue;
        }
        else if (string[index] == 'e')
        {
          Append(operands, Num(M_E));
          mayunary = 0;
          continue;
        }
        if (mayunary && (string[index] == '+' || string[index] == '-' || isalpha(string[index])))
        {
          if (string[index] == '+')
            continue;
          copy = ReadOp((char*) string, indexptr, 1);
          cur_op = DefineUnaryOp(copy);
          free(copy);
          if (cur_op == INVALID)
          {
            break;
          }
        }
        else
          cur_op = DefineBinaryOp(string[index]);
        while ((operations->depth_ && operands->depth_) &&
            (!(IsUnaryOp(cur_op) || cur_op == BEXP) && GetPriority(Back(operations)) >= GetPriority(cur_op)
                || (IsUnaryOp(cur_op) && Back(operations) != BEXP || cur_op == BEXP)
                    && GetPriority(Back(operations)) > GetPriority(cur_op)))
          Process(operands, operations, lastError);
        Append_op(operations, cur_op);
        mayunary = 1;
      }
      else if (isdigit(string[index]) || string[index] == '.')
      {
        copy = ReadOp(string, indexptr, 0);
        if (copy)
        {
          node_t number = Num(atof(copy));
          free(copy);
          Append(operands, number);
          mayunary = 0;
        }
        else
          *lastError = ERR_WRONG_EXPRESSION;
      }
      else
        break;
    }
  free((char*) string);
  while (operations->depth_)
    Process(operands, operations, lastError);
  if (*lastError == ERR_OK && operands->depth_ == 1 && operations->depth_ == 0)
    return operands->elements_[0];
  else if (operands->depth_ > 0)
    for (index = 0; index < operands->depth_; index++)
      Free(operands->elements_[index]);
  return NULL;
}