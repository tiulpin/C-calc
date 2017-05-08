#pragma once
#include <stdlib.h>
/**
 * \file Stack.h
 * \author Viktor Tiulpin <viktor@tiulpin.me>
 * \version 0.9
 * \section DESCRIPTION
 * Converts math expression to Reverse-Polish-Notation using Shunting-yard algorithm and evaluates them.
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
typedef enum
{
  ERR_OK,
  ERR_NOT_ENOUGH_MEMORY,
  ERR_WRONG_EXPRESSION,
  ERR_INVALID_OP_PROCESSING,
  ERR_BRACKETS,
  ERR_INVALID_B_OP,
  ERR_READING_NUM,
  ERR_INF_NAN,
  ERR_INCORRECT_CONVERT,
  ERR_INVALID_U_OP,
  ERR_SC_NOTATION
} error_t;
typedef enum
{
  FALSE = 0,
  TRUE = 1,
} bool_t;
enum Binary_op
{
  B_OP_INVALID = -1, B_OP_EXP, B_OP_TIMES, B_OP_DIVIDE, B_OP_PLUS, B_OP_MINUS,
};
enum Unary_op
{
  U_OP_INVALID = -1,
  U_OP_NEG,
  U_OP_POS,
  U_OP_SQRT,
  U_OP_SIN,
  U_OP_COS,
  U_OP_TAN,
  U_OP_CTG,
  U_OP_ASIN,
  U_OP_ACOS,
  U_OP_ATAN,
  U_OP_LN,
  U_OP_FLOOR,
  U_OP_CEIL,
  U_OP_LOG
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
  LOG
};
enum Node_type
{
  NUM, B_OP, U_OP
};
struct Node /* Node, which represents number, binary operation or unary operation */
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
struct stack_t /* Operand stack */
{
  unsigned int depth_;
  node_t elements_[100];
};
struct opstack_t /* Operation stack */
{
  unsigned int depth_;
  enum Op elements_[100];
};
/**
 * Function that converts binary operation to node.
 * \param[in] left Left operand node
 * \param[in] right Right operand node
 * \return node expression
 */
node_t b_op(node_t left, node_t right, enum Binary_op bin_);
/**
 * Function that converts unary operation to node.
 * \param[in] only Only operand node
 * \return node expression
 */
node_t u_op(node_t only, enum Unary_op un_);
/**
 * Function that pops operand node from operand stack.
 * \param[out] stack Stack of operands
 * \return node expression
 */
node_t Pop(struct stack_t* stack);
/**
 * Function that converts number to number node.
 * \param[in] number Number
 * \return node expression
 */
node_t Num(double number);
/**
 * Function that appends operation enum to Operation stack.
 * \param[out] stack Stack of operations
 * \param[in] op Enum operation
 */
void Append_op(struct opstack_t* op_stack, enum Op op);
/**
 * Function that appends operand node to Operand stack.
 * \param[out] stack Stack of operands
 * \param[in] node Operand
 */
void Append(struct stack_t* stack, node_t node);
/**
 * Function that appends operation enum to Operation stack.
 * \param[out] stack Stack of operations
 * \return op Enum operation
 */
enum Op Pop_op(struct opstack_t* op_stack);
/**
 * Function that converts math expression to Reverse-Polish-Notation using Shunting-yard algorithm.
 * \param[out] op_stack Operation stack
 * \return enum Operation
 */
enum Op Back(struct opstack_t* op_stack);
/**
 * Function that initializes Operands stack.
 */
struct opstack_t* InitOperations();
/**
 * Function that initializes Operands stack.
 */
struct stack_t* InitOperands();
/**
 * Function that frees node.
 * \param[in] node Node
 */
void Free(node_t node);