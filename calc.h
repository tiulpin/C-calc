//
// Created by tiulpin on 23.04.17.
//
#pragma once

#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "other.h"
#include "data.h"

double Sum(double a, double b);

double Sub(double a, double b);

double Mul(double a, double b);

double Div(double a, double b);

double Calculate(char const *expression, error_t *lastError);
