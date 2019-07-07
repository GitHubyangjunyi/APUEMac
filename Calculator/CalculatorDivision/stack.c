//
//  stack.c
//  CalculatorDivision
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include "stack.h"

#define MAXVAL 100    //栈val的最大深度

int sp = 0;            //下一个空闲栈位置
double val[MAXVAL];    //值栈
//如果变量定义在任何函数的外部,则称为外部变量,所以把push和pop必须共享的栈和栈顶指针定义在这两个函数外部,但是main函数本身并没有引用栈或栈顶指针,因此对main而言要隐藏它们
void push(double f)//把f压入到值栈中
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)//弹出并返回栈顶的值
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
