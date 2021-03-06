// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../headers/Convert.h"
#include "../headers/ConvertHelp.h"
char *ReadOp(const char *string, int *index, bool_t IsOperation, error_t *lastError)
{
  int current = 0;
  char *copy = malloc(sizeof(char));
  if (copy == NULL)
  {
    *lastError = ERR_NOT_ENOUGH_MEMORY;
    return NULL;
  }
  char *buffer = NULL;
  if (IsOperation)
  {
    while (isalpha(string[*index]) && *lastError == ERR_OK)
    {
      copy[current] = string[(*index)++];
      buffer = (char *) realloc(copy, sizeof(char) * (++current + 1));
      if (buffer == NULL)
      {
        *lastError = ERR_NOT_ENOUGH_MEMORY;
        return NULL;
      }
      copy = buffer;
    }
  }
  else
  {
    bool_t exp = FALSE;
    bool_t sign = FALSE;
    while ((isdigit(string[*index]) || string[*index] == '.') ||
        ((string[*index] == 'E' || string[*index] == 'e') && !exp) ||
        ((string[*index] == '+' || string[*index] == '-') && !sign))
    {
      if (string[*index] == 'E' || string[*index] == 'e')
      {
        exp = TRUE;
      }
      else if (string[*index] == '+' || string[*index] == '-')
      {
        sign = TRUE;
      }
      copy[current] = string[(*index)++]; /* add symbol from the input line to number and increase index */
      buffer = (char *) realloc(copy, sizeof(char) * (++current + 1));
      if (buffer == NULL)
      {
        *lastError = ERR_NOT_ENOUGH_MEMORY;
        return NULL;
      }
      copy = buffer;
      if ((exp && string[*index] == '.') || (string[*index] == '.' && !isdigit(string[*index + 1])))
      {
        *lastError = ERR_SC_NOTATION;
      }
    }
    if (!isdigit(copy[current - 1]))
    { /* check cases like "1e1+" or "1e" or '.' and "..."*/
      *lastError = ERR_SC_NOTATION;
    }
  }
  copy[current] = 0; /* terminates the string */
  (*index)--;
  return copy;
}
enum Binary_op ToBinary_op(enum Op op)
{
  int i;
  enum Op OP[] = {PLUS, MINUS, TIMES, DIVIDE, BEXP};
  enum Binary_op BOP[] = {B_OP_PLUS, B_OP_MINUS, B_OP_TIMES, B_OP_DIVIDE, B_OP_EXP};
  for (i = 0; i < 5; i++)
    if (op == OP[i])
    {
      return BOP[i];
    }
  return B_OP_INVALID;
}
enum Unary_op ToUnary_op(enum Op op)
{
  int i;
  enum Op OP[] = {NEG, POS, SQRT, SIN, COS, TAN, CTG, ASIN, ACOS, ATAN, LN, FLOOR, CEIL};
  enum Unary_op UOP[] =
      {U_OP_NEG, U_OP_POS, U_OP_SQRT, U_OP_SIN, U_OP_COS, U_OP_TAN, U_OP_CTG, U_OP_ASIN, U_OP_ACOS, U_OP_ATAN, U_OP_LN,
       U_OP_FLOOR, U_OP_CEIL};
  for (i = 0; i < 13; i++)
    if (op == OP[i])
    {
      return UOP[i];
    }
  return U_OP_INVALID;
}
enum Op DefineBinaryOp(char op)
{
  int i;
  enum Op BOP[] = {PLUS, MINUS, TIMES, DIVIDE, BEXP};
  char symbol[] = {'+', '-', '*', '/', '^'};
  for (i = 0; i < 5; i++)
    if (op == symbol[i])
    {
      return BOP[i];
    }
  return INVALID;
}
enum Op DefineUnaryOp(char *op)
{
  int i;
  char *word[] = {"sqrt", "sin", "cos", "tg", "ctg", "arcsin", "arccos", "arctg", "ln", "floor", "ceil"};
  enum Op UOP[] = {SQRT, SIN, COS, TAN, CTG, ASIN, ACOS, ATAN, LN, FLOOR, CEIL};
  for (i = 0; i < 11; i++)
    if (strcmp(op, word[i]) == 0)
    {
      return UOP[i];
    }
  return INVALID;
}
void Process(struct stack_t *operands, struct opstack_t *operations, error_t *lastError)
{
  enum Op op;
  if (operations->depth_ == 0)
  {
    *lastError = ERR_INVALID_OP_PROCESSING;
    return;
  }
  op = Pop_op(operations);
  switch (op)
  {
  case POS:
  case NEG:
  case SQRT:
  case SIN:
  case COS:
  case TAN:
  case CTG:
  case ASIN:
  case ACOS:
  case ATAN:
  case LN:
  case FLOOR:
  case CEIL:
  {
    if (operands->depth_ == 0)
    {
      *lastError = ERR_INVALID_OP_PROCESSING;
      return;
    }
    node_t only = Pop(operands);
    node_t new_node = u_op(only, ToUnary_op(op));
    if (new_node == NULL)
    {
      *lastError = ERR_NOT_ENOUGH_MEMORY;
      return;
    }
    Append(operands, new_node);
    return;
  }
  case PLUS:
  case MINUS:
  case TIMES:
  case DIVIDE:
  case BEXP:
  {
    if (operands->depth_ < 2)
    {
      *lastError = ERR_INVALID_OP_PROCESSING;
      return;
    }
    node_t right = Pop(operands);
    node_t left = Pop(operands);
    node_t new_node = b_op(left, right, ToBinary_op(op));
    if (new_node == NULL)
    {
      *lastError = ERR_NOT_ENOUGH_MEMORY;
      return;
    }
    Append(operands, new_node);
    return;
  }
  default:
    *lastError = ERR_INVALID_OP_PROCESSING;
  }
}
bool_t IsOperatorOrConst(char op)
{
  if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || isalpha(op))
  {
    return TRUE;
  }
  return FALSE;
}
bool_t IsOPAR(struct opstack_t *operations)
{
  int i;
  for (i = 0; i < operations->depth_; i++)
    if (operations->elements_[i] == OPAR)
    {
      return TRUE;
    }
  return FALSE;
}
bool_t IsUnaryOp(enum Op op)
{
  if (ToBinary_op(op) == B_OP_INVALID && op != OPAR)
  {
    return TRUE;
  }
  return FALSE;
}
int GetPriority(enum Op op)
{
  return op == OPAR ? -1 : op == PLUS ||
      op == MINUS ? 1 : op == TIMES ||
      op == DIVIDE ? 2 : IsUnaryOp(op) ? 3 : op == BEXP ? 4 : -1;
}
node_t Convert(char *string, error_t *lastError)
{
  int index;
  int minus = 0;
  char *copy;
  enum Op cur_op;
  int mayunary = 1;
  struct opstack_t *operations = InitOperations();
  struct stack_t *operands = InitOperands();
  for (index = 0; string[index] != 0 && *lastError == ERR_OK; ++index)
    if (isgraph(string[index])) /* ignores space symbols */
    {
      if (string[index] == '(')
      {
        Append_op(operations, OPAR);
        mayunary = 1;
      }
      else if (string[index] == ')')
      {
        if (operands->depth_ && IsOPAR(operations))
        {
          while (operations->depth_ != 0 && Back(operations) != OPAR && *lastError == ERR_OK)
            Process(operands, operations, lastError);
          if ((operations->depth_ > 1 && *lastError == ERR_OK)
              && IsUnaryOp(operations->elements_[operations->depth_ - 2])
              && Back(operations) == OPAR)
          {
            mayunary = 1;
            Pop_op(operations);
            Process(operands, operations, lastError);
          }
          if (!mayunary && operations->depth_ != 0 && Back(operations) == OPAR)
          {
            Pop_op(operations);
          }
          mayunary = 0;
        }
        else
        {
          *lastError = ERR_BRACKETS;
        }
      }
      else if (IsOperatorOrConst(string[index])) /*checks operators or constants like pi or e*/
      {
        if ((string[index] == 'p' && string[index + 1] == 'i') || string[index] == 'e')
        {
          node_t C;
          if (string[index] == 'e')
          {
            C = num(M_E);
          }
          else
          {
            C = num(M_PI);
          }
          if (C == NULL)
          {
            *lastError = ERR_NOT_ENOUGH_MEMORY;
            break;
          }
          Append(operands, C);
          if (C->number_ == M_PI)
          {
            index++;
          } /*'pi' - two symbols, not one (not 'e')*/
          mayunary = 0;
          continue;
        }
        if (mayunary && (string[index] == '+' || string[index] == '-' || isalpha(string[index]))) /* is unary? */
        {
          switch (string[index])
          {
          case '+':
            continue;
          case '-':
          {
            minus++;
            while (string[index] == '-' && string[index + 1] == '-')
            {
              index++;
              minus++;
            }
            if (minus & 1)
            {
              cur_op = NEG;
            }
            else
            {
              continue;
            }
            break;
          }
          default:
            copy = ReadOp(string, &index, TRUE, lastError);
            if (copy == NULL)
            {
              *lastError = ERR_NOT_ENOUGH_MEMORY;
              return NULL;
            }
            cur_op = DefineUnaryOp(copy);
            free(copy);
            if (cur_op == INVALID)
            {
              *lastError = ERR_INVALID_U_OP;
              break;
            }
          }
        }
        else
        {
          cur_op = DefineBinaryOp(string[index]);
          if (cur_op == INVALID)
          {
            *lastError = ERR_INVALID_B_OP;
          }
        }
        while ((operations->depth_ && operands->depth_ && *lastError == ERR_OK) &&
            ((!(IsUnaryOp(cur_op) || cur_op == BEXP) && GetPriority(Back(operations)) >= GetPriority(cur_op))
                || (((IsUnaryOp(cur_op) && Back(operations) != BEXP) || cur_op == BEXP)
                    && GetPriority(Back(operations)) > GetPriority(cur_op))))
          Process(operands, operations, lastError);
        if (*lastError != ERR_OK)
        {
          break;
        }
        Append_op(operations, cur_op);
        mayunary = 1;
      }
      else if (isdigit(string[index]) || string[index] == '.')
      {
        copy = ReadOp(string, &index, FALSE, lastError);
        if (copy == NULL)
        {
          *lastError = ERR_NOT_ENOUGH_MEMORY;
          return NULL;
        }
        if (*lastError == ERR_OK)
        {
          node_t number = num(atof(copy));
          free(copy);
          if (number == NULL)
          {
            *lastError = ERR_NOT_ENOUGH_MEMORY;
            return NULL;
          }
          Append(operands, number);
          mayunary = 0;
        }
        else
        {
          free(copy);
          if (*lastError == ERR_OK)
          {
            *lastError = ERR_READING_NUM;
          }
        }
      }
      else if (*lastError == ERR_OK)
      {
        *lastError = ERR_WRONG_EXPRESSION;
      }
    }
  while (operations->depth_ && *lastError == ERR_OK)
    Process(operands, operations, lastError);
  if (*lastError == ERR_OK && operands->depth_ == 1 && operations->depth_ == 0)
  {
    return operands->elements_[0];
  }
  if (operands->depth_ > 0)
  {
    for (index = 0; index < operands->depth_; index++)
      Free(operands->elements_[index]);
  }
  return NULL;
}