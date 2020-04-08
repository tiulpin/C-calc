// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../headers/Stack.h"
#include <time.h>
node_t num(double number)
{
  node_t node = (node_t) malloc(sizeof(struct Node));
  if (node == NULL)
  {
    return NULL;
  }
  node->type_ = NUM;
  node->number_ = number;
  return node;
}
node_t b_op(node_t left, node_t right, enum Binary_op binary_op)
{
  node_t node = (node_t) malloc(sizeof(struct Node));
  if (node == NULL)
  {
    return NULL;
  }
  node->type_ = B_OP;
  node->bin_ = binary_op;
  node->left = left;
  node->right = right;
  return node;
}
node_t u_op(node_t only, enum Unary_op unary_op)
{
  node_t node = (node_t) malloc(sizeof(struct Node));
  if (node == NULL)
  {
    return NULL;
  }
  node->type_ = U_OP;
  node->un_ = unary_op;
  node->only = only;
  return node;
}
void Append(struct stack_t *stack, node_t node)
{
  stack->elements_[stack->depth_] = node;
  stack->depth_++;
}
node_t Pop(struct stack_t *stack)
{
  stack->depth_--;
  return stack->elements_[stack->depth_];
}
void Append_op(struct opstack_t *operations, enum Op op)
{
  operations->elements_[operations->depth_] = op;
  operations->depth_++;
}
void Free(node_t node)
{
  switch (node->type_)
  {
  case B_OP:
    Free(node->left);
    Free(node->right);
    break;
  case U_OP:
    Free(node->only);
    break;
  default:
    break;
  }
  free(node);
}
struct opstack_t *InitOperations()
{
  static struct opstack_t operations;
  operations.depth_ = 0;
  return (&operations);
}
struct stack_t *InitOperands()
{
  static struct stack_t operands;
  operands.depth_ = 0;
  return (&operands);
}
enum Op Back(struct opstack_t *operations)
{
  return operations->elements_[operations->depth_ - 1];
}
enum Op Pop_op(struct opstack_t *operations)
{
  operations->depth_--;
  return operations->elements_[operations->depth_];
}