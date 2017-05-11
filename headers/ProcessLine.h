// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "Stack.h"
/**
 * \file ProcessLine.h
 * \author Viktor Tiulpin <viktor@tiulpin.me>
 * \version 0.9
 */
/**
 * Function that processes the line: calls Calculate and Convert functions.
 * \param[out] line Expression string
 * \param[out] lastError Error code
 */
void ProcessLine(char* line, error_t* lastError);
/**
 * Function that reports errors.
 * \param[in] codeerror Error code.
 */
void ReportError(error_t lastError, char* line);