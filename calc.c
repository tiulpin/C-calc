//
// Created by tiulpin on 23.04.17.
//
#include "calc.h"

double Sum(double a, double b) {
    return (a + b);
}

double Sub(double a, double b) {
    return (a - b);
}

double Mul(double a, double b) {
    return (a * b);
}

double Div(double a, double b) {
    return (a / b);
}

double Calculate(char const *expression, error_t *error) {//Check brackets
    double result;
    char *p_expression = rpn(expression);
    if (*error != ERR_OK)
        return 0.0;
    stack_t *stack = initializeStack();
    double (*p)(double, double) = NULL;
    double arg;
    char *n;
    int i;
    int j;
    for (i = 0; p_expression[i = skipSpaces((char const *) p_expression, i)] != '\0'; i++) {
        if (isOperator(p_expression[i])) {
            switch (p_expression[i]) {
                case '+':
                    p = &Sum;
                    break;
                case '-':
                    p = &Sub;
                    break;
                case '*':
                    p = &Mul;
                    break;
                case '/':
                    p = &Div;
                    break;
                case '^':
                    p = &pow;
                    break;
                default:
                    p = &Sum;
                    break;
            }
            arg = p(pop(stack), pop(stack));
            append(stack, arg);
        } else if (isalnum(p_expression[i])) {
            n = malloc(sizeof(char));
            j = 0;
            do {
                n[j] = p_expression[i];
                j++;
                i++;
                n = realloc(n, sizeof(char) * (j + 1));
            } while (isalnum(p_expression[i])); //double?
            n[j] = '\0';
            arg = atof((const char *) n);
            append(stack, arg);
            free(n);
            i--;
        }
    }
    result = pop(stack);
    removeStack(stack);
    free(p_expression);
    if (result == -0.0 || *error != ERR_OK) result = 0.0; //Check errors
    return result;
}