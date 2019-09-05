//
//  getop.c
//  CalculatorDivision
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include "CalculatorDivision.h"

int getop(char s[])//获取下一个运算符或数值操作数,需要跳过空格与制表符,如果下一个字符不是数字或小数点,则返回,否则把这些数字字符串收集起来,并返回NUMBER,以标识数已经收集起来了
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')//跳过空格或者制表符
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')//不是数或不是小数点则返回操作符
        return c;
    i = 0;
    if (isdigit(c))//收集整数部分
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')//收集小数部分
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)//如果c未到达末尾则反读一个字符
        ungetchs(c);
    return NUMBER;
}
