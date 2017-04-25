//
// Created by tiulpin on 23.04.17.
//
#pragma once

#include <stdio.h>
#include <ctype.h>
#include "other.h"
#include "stdlib.h"

typedef enum {
    ERR_OK,
    ERR_NOT_ENOUGH_MEMORY,
    ERR_WRONG_EXPRESSION,
    ERR_MEMORY_LEAKS,
    ERR_NOT_DEFINED,
    ERR_BRACKETS,
} error_t;

char const *GetErrorString(error_t error);

void ProcessLine(char const *line, error_t *lastError);

char *ReadLine(FILE *in, error_t *lastError);

error_t ReportError(error_t error);

int NeedCalculate(char const *);

int isOperator(char c);