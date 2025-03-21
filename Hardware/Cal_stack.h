#ifndef __CAL_STACK_H
#define __CAL_STACK_H
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20
typedef struct
{
    char* base_op;//ջ��ָ��
    char* top_op;//ջ��ָ��
    int stacksize;//ջ�����������
}SqStack_op;//�ַ�ջ

typedef struct
{
    double* base;
    double* top;
    int stacksize;
}SqStack;//����ջ

int InitStack_op(SqStack_op* S);
int InitStack(SqStack* S);
int StackEmpty_op(SqStack_op* S);
int StackEmpty(SqStack* S);
int Push_op(SqStack_op* S, char e);
int Push(SqStack* S, double e);
int Pop_op(SqStack_op* S, char* e);
int Pop(SqStack* S, double* e);
char GetTop_op(SqStack_op* S);
double GetTop(SqStack* S);
int DestroyStark_op(SqStack_op* S);
int DestroyStark(SqStack* S);
int ClearStark(SqStack* S);
int ClearStark_op(SqStack_op* S);

#endif

