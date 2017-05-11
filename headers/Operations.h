// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <math.h>
/**
 * \file Operations.h
 * \author Viktor Tiulpin <viktor@tiulpin.me>
 * \version 0.9
 * \section DESCRIPTION
 * Converts math expression to Reverse-Polish-Notation using Shunting-yard algorithm and evaluates them.
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */

/**
 * Function that returns sum of two operands.
 * \param[in] left Left operand
 * \param[in] right Right operand
 * \return double Result of evaluation
 */
double sum(double left, double right);
/**
 * Function that returns subtraction of two operands.
 * \param[in] left Left operand
 * \param[in] right Right operand
 * \return double Result of evaluation
 */
double sub(double left, double right);
/**
 * Function that returns multiplication of two operands.
 * \param[in] left Left operand
 * \param[in] right Right operand
 * \return double Result of evaluation
 */
double mul(double left, double right);
/**
 * Function that returns division of two operands.
 * \param[in] left Left operand
 * \param[in] right Right operand
 * \return double Result of evaluation
 */
double din(double left, double right);
/**
 * Function that returns negative value of the input operand.
 * \param[in] only Operand
 * \return double Result of evaluation
 */
double neg(double only);
/**
 * Function that returns value of the input operand.
 * \param[in] only Operand
 * \return double Result of evaluation
 */
double pos(double only);
/**
 * Function that returns ctan of the input operand.
 * \param[in] left Left operand
 * \return double Result of evaluation
 */
double ctg(double only);
/*Arrays of function pointers*/
double (* UOPS[])(double) = {neg, pos, sqrt, sin, cos, tan, ctg, asin, acos, atan, log, floor, ceil};
double (* BOPS[])(double, double) = {pow, mul, din, sum, sub};