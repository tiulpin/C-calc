//
// Created by tiulpin on 23.04.17.
//
#include "data.h"

stack_t *initializeStack() {
  stack_t *this = malloc(sizeof(stack_t));
  this->size_ = 100;
  this->data_ = malloc(this->size_ * sizeof(double));
  this->top_ = 0;
  return this;
}

void resizeStack(stack_t *this) {
  double *data_;
  this->size_++;
  data_ = realloc(this->data_, this->size_ * sizeof(double));
  this->data_ = data_;
}

void removeStack(stack_t *this) {
  free(this->data_);
  this->data_ = NULL;
  free(this);
  this = NULL;
}

double pop(stack_t *this) {
  if (this->top_ == 0) return 0.0;
  return this->data_[--this->top_];
}

void append(stack_t *this, double arg) {
  if (this->top_ > this->size_) resizeStack(this);
  this->data_[this->top_++] = arg;
}

int skipSpaces(char const *expression, int i) {
  while ((expression[i] != '\0') && (isspace(expression[i])))
    i++;
  return i;
}

int getPriority(char s) {
  switch (s) {
    case '^':return 3;
    case '*':return 2;
    case '/':return 2;
    case '+':return 1;
    case '-':return 1;
    default:return 0;
  }
}

char *stExp(char *p_expression, int *endptr, stack_t *stack) {
  p_expression[(*endptr)++] = ' ';
  p_expression = realloc(p_expression, sizeof(char) * (*endptr + 1));

  p_expression[(*endptr)++] = (char) pop(stack);
  p_expression = realloc(p_expression, sizeof(char) * (*endptr + 1));

  return p_expression;
}

char *rpn(char const *expression) {
  char *p_expression = malloc(sizeof(char));
  stack_t *stack = initializeStack();
  int priority;
  int end = 0;
  int start;
  int *endptr = &end;
  for (start = 0; expression[start = skipSpaces(expression, start)] != '\0'; start++) {
    if (isalnum(expression[start])) {
      while (isalnum(expression[start]) || (expression[start] == '.')) {
        p_expression[end] = expression[start++];
        p_expression = realloc(p_expression, sizeof(char) * (++end + 1));
      }
      start--;
      p_expression[end++] = ' ';
      p_expression = realloc(p_expression, sizeof(char) * (end + 1));
    }
    if (isOperator(expression[start])) {
      priority = getPriority(expression[start]);
      if ((priority == 1) && ((stack->data_[stack->top_ - 1] == '(') || (stack->top_ == 0)))
        append(stack, (double) expression[start]);
      else if (priority == 1) {
        while ((stack->data_[stack->top_ - 1] != '(') && (stack->top_ != 0))
          p_expression = stExp(p_expression, endptr, stack);
        append(stack, (double) expression[start]);
      }
      if ((priority == 2) && ((getPriority((char) stack->data_[stack->top_ - 1]) == 1)
          || (stack->data_[stack->top_ - 1] == '(') || (stack->top_ == 0)))
        append(stack, (double) expression[start]);
      else if (priority == 2) {
        while ((stack->data_[stack->top_ - 1] != '(') &&
            (getPriority((char) stack->data_[stack->top_ - 1]) != 1)
            && (stack->top_ != 0))
          p_expression = stExp(p_expression, endptr, stack);
        append(stack, (double) expression[start]);
      }
      if ((priority == 3) || (expression[start] == '(')) append(stack, (double) expression[start]);
      if (expression[start] == ')') {
        while (stack->data_[stack->top_ - 1] != '(') p_expression = stExp(p_expression, endptr, stack);
        pop(stack);
      }
    }
  }
  while (stack->top_ != 0) p_expression = stExp(p_expression, endptr, stack);
  p_expression[end] = '\0';
  removeStack(stack);
  return p_expression;
}