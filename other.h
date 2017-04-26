//
// Created by tiulpin on 23.04.17.
//
#ifndef CALC_TIULPIN_OTHER_H
#define CALC_TIULPIN_OTHER_H
#pragma once
#endif //CALC_TIULPIN_TT_H
#include <stdio.h>
#include <ctype.h>
#include "stdlib.h"
typedef enum
{
  ERR_OK,
  ERR_NOT_ENOUGH_MEMORY,
  ERR_WRONG_EXPRESSION,
} error_t;
char const* GetErrorString(error_t error);
void ProcessLine(char const* line, error_t* lastError);
char* ReadLine(FILE* in, error_t* lastError);
error_t ReportError(error_t error);
int NeedCalculate(char const*);
int IsOperator(char c);