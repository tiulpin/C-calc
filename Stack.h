#pragma once
#include <stdlib.h>
typedef enum
{
  ERR_OK, ERR_NOT_ENOUGH_MEMORY, ERR_WRONG_EXPRESSION,
} error_t;
enum Binary_op
{
  B_OP_INVALID, B_OP_EXP, B_OP_TIMES, B_OP_DIVIDE, B_OP_PLUS, B_OP_MINUS,
};
enum Unary_op
{
  U_OP_INVALID, U_OP_NEG, U_OP_POS, U_OP_SQRT, U_OP_SIN, U_OP_COS, U_OP_TAN, U_OP_CTG, U_OP_ASIN, U_OP_ACOS, U_OP_ATAN,
  U_OP_LN, U_OP_FLOOR, U_OP_CEIL,
};
enum Op
{
  INVALID,
  NEG,
  POS,
  SQRT,
  SIN,
  COS,
  TAN,
  CTG,
  ASIN,
  ACOS,
  ATAN,
  LN,
  FLOOR,
  CEIL,
  BEXP,
  TIMES,
  DIVIDE,
  PLUS,
  MINUS,
  OPAR,
};
enum Node_type
{
  NUM, B_OP, U_OP
};
struct Node
{
  enum Node_type type_;
  enum Binary_op bin_;
  enum Unary_op un_;
  struct Node* left;
  struct Node* right;
  struct Node* only;
  double number_;
};
typedef struct Node* node_t;
struct stack_t
{
  unsigned int depth_;
  node_t elements_[42];
};
struct opstack_t
{
  unsigned int depth_;
  enum Op elements_[42];
};
node_t b_op(node_t left, node_t right, enum Binary_op bin_);
node_t u_op(node_t only, enum Unary_op un_);
node_t Pop(struct stack_t* stack);
node_t Num(double number);
void Append_op(struct opstack_t* op_stack, enum Op op);
void Append(struct stack_t* stack, node_t node);
enum Op Pop_op(struct opstack_t* op_stack);
enum Op Back(struct opstack_t* op_stack);
enum Binary_op ToBinary_op(enum Op op);
enum Unary_op ToUnary_op(enum Op op);
struct opstack_t* InitOperations();
struct stack_t* InitOperands();
void Free(node_t node);