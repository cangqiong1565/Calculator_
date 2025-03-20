#ifndef __Cal_algorithm_H
#define __Cal_algorithm_H

#include"stdio.h"
#include <ctype.h>
#include"Cal_stack.h"

double Integrate(double a, double b);
double Cumulative_function(double x);
double applyOp(double a, double b, char op);
int precedence(char op);
void extract(char str[], SqStack_op* _op, SqStack* _Value);

#endif
