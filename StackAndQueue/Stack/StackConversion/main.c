//
//  main.c
//  StackConversion
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 64
typedef int datatype;
typedef struct Stack
{
    datatype stack[STACK_SIZE];//栈空间
    int top;                    //栈顶指针,约定栈空top = -1,栈满top = STACK_SIZE - 1
}SequentialStack;

void Conversion(SequentialStack *s, int n);
void InitSequentialStack(SequentialStack *s);
int EmptySequentialStack(SequentialStack *s);
int PushSequentialStack(SequentialStack *s, datatype x);
int PopSequentialStack(SequentialStack *s, datatype *x);

int main(int argc, const char * argv[]) {
    
    
    SequentialStack s;
    InitSequentialStack(&s);
    
    Conversion(&s, 1348);//2504
    
    
    return 0;
}

void Conversion(SequentialStack * s, int n)//输入一个非负的十进制数n,输出转换后的八进制
{
    int e;
    while (n)
    {
        PushSequentialStack(s, n % 8);
        n = n / 8;
    }
    while (!EmptySequentialStack(s))
    {
        PopSequentialStack(s, &e);
        printf("%d", e);
    }
}

void InitSequentialStack(SequentialStack * s)//初始化顺序栈为空栈
{
    s->top = -1;
}

int EmptySequentialStack(SequentialStack * s)//判断顺序栈是否为空,空返回1,非空返回0
{
    return (s->top == -1);
}

int PushSequentialStack(SequentialStack * s, datatype x)//压栈函数
{
    if (s->top == STACK_SIZE - 1)
    {
        return false;
    }
    else
    {
        s->top++;
        s->stack[s->top] = x;
        return true;
    }
}

int PopSequentialStack(SequentialStack * s, datatype * x)
{
    if (s->top == -1)
    {
        return false;
    }
    else
    {
        *x = s->stack[s->top];
        s->top--;
        return true;
    }
}

