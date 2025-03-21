#ifndef __Cal_algorithm_H
#define __Cal_algorithm_H

#include"stdio.h"
#include <ctype.h>
#include"Cal_stack.h"
#include"math.h"

double Integrate(double a, double b);
double Cumulative_function(double x);
double applyOp(double a, double b, char op);
int precedence(char op);
void extract(char _str[], SqStack_op* _Stack_Op, SqStack*_Stack_Num);
void splitNumber(int* int_long, int* porint_long, double num);
double Trig(char a, double b);

#endif

