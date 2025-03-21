#ifndef __CACULATOR_H
#define __CACULATOR_H

#include "stm32f10x.h"
#include "bsp_OLED.h"

// 共享变量声明
extern char arr[100];
extern int flag;

extern Stack _NumInput;
extern SqStack_op _op;
extern SqStack _Value;

#endif
