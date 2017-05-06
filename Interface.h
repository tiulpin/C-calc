#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "Stack.h"
void ProcessLine(char* line, error_t* lastError);
char* ReadLine(FILE* in, error_t* lastError);
int IsOperator(char op);