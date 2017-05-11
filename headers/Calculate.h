// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Stack.h"
#include <math.h>
/**
 * \file Calculate.h
 * \author Viktor Tiulpin <viktor@tiulpin.me>
 * \version 0.9
 * \section DESCRIPTION
 * Converts math expression to Reverse-Polish-Notation using Shunting-yard algorithm and evaluates them.
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
/**
 * Function that processes the line: calls Calculate and Convert functions.
 * \param[in] node postfix-expression
 * \param[out] lastError Error code
 * \return double Result of evaluation
 */
double Calculate(node_t node, error_t* lastError);