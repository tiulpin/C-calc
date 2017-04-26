//
// Created by tiulpin on 24.04.17.
//
#ifndef CALC_TIULPIN_DATA_H
#define CALC_TIULPIN_DATA_H
#pragma once
#endif //CALC_TIULPIN_DATA_H
#include "calc.h"
#include <stdlib.h>
typedef struct
{
  error_t Error;
  double* data_;
  int size_;
  int top_;
} stack_t;
char* StExp(char* p_expression, int* endptr, stack_t* stack);
int GetPriority(char s);
char* Convert(char const* expression);
void Append(stack_t* stack, double arg);
double Pop(stack_t* stack);
void ResizeStack(stack_t* stack);
stack_t* InitializeStack();
void RemoveStack(stack_t* stack);
int SkipSpaces(char const* expression, int i);