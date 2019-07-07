//
//  main.c
//  SequentialStack
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 64
typedef char datatype;
typedef struct Stack
{
    datatype stack[STACK_SIZE];
    int top;
}SequentialStack;

void InitSequentialStack(SequentialStack *s);
int EmptySequentialStack(SequentialStack *s);
int PushSequentialStack(SequentialStack *s, datatype x);
int PushSequentialStackTest(SequentialStack s, datatype x);
int PopSequentialStack(SequentialStack *s, datatype *x);
int GetSequentialStack(SequentialStack *s, datatype *x);

int main(int argc, const char * argv[]) {
    

    SequentialStack sestacktest;
    int sign;
    InitSequentialStack(&sestacktest);
    sign = PushSequentialStackTest(sestacktest, 'a');
    printf("%d %c\n", sign, sestacktest.stack[sestacktest.top]);
    sign = PushSequentialStackTest(sestacktest, 'b');
    printf("%d %c\n", sign, sestacktest.stack[sestacktest.top]);
    
    
    SequentialStack stack;
    InitSequentialStack(&stack);
    PushSequentialStack(&stack, 'a');
    PushSequentialStack(&stack, 'b');
    PushSequentialStack(&stack, 'c');
    
    datatype x = NULL;
    PopSequentialStack(&stack, &x);
    printf("%c\n", x);
    GetSequentialStack(&stack, &x);
    printf("%c\n", x);
    PushSequentialStack(&stack, 'x');
    
    
    return 0;
}

void InitSequentialStack(SequentialStack * s)
{
    s->top = -1;
}

int EmptySequentialStack(SequentialStack * s)
{
    return (s->top == -1);
}

int PushSequentialStack(SequentialStack * s, datatype x)
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

int PushSequentialStackTest(SequentialStack s, datatype x)
{
    if (s.top == STACK_SIZE - 1)
    {
        return false;
    }
    else
    {
        s.top++;
        s.stack[s.top] = x;
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

int GetSequentialStack(SequentialStack * s, datatype * x)
{
    if (s->top == -1)
    {
        return false;
    }
    else
    {
        *x = s->stack[s->top];
        return true;
    }
}
