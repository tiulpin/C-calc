#include "Stack.h"
#include "Interface.h"
#pragma once
void Process(struct stack_t* stack, struct opstack_t* opstack, error_t* lastError);
node_t Convert(char* string, error_t* lastError);