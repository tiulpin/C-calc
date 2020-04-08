// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "ProcessLine.h"
#include "Stack.h"
/**
 * \file SortStation.h
 * \author Viktor Tiulpin <viktor@tiulp.in>
 * \version 1.0
 */
/**
 * Function that converts math expression to Reverse-Polish-Notation using Shunting-yard algorithm.
 * \param[in] line Expression string
 * \param[out] lastError Error code
 * \return node expression
 */
node_t Convert(char *string, error_t *lastError);