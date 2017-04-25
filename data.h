//
// Created by tiulpin on 24.04.17.
//
#pragma once

#include "calc.h"
#include <stdlib.h>

typedef struct {
    error_t Error;
    double *data_;
    int size_;
    int top_;
} stack_t;

char *stExp(char *p_expression, int *endptr, stack_t *stack);

int getPriority(char s);

char *rpn(char const *expression);

void append(stack_t *stack, double arg);

double pop(stack_t *stack);

void resizeStack(stack_t *stack);

stack_t *initializeStack();

void removeStack(stack_t *stack);

int skipSpaces(char const *expression, int i);