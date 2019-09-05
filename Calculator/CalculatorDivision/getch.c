//
//  getch.c
//  CalculatorDivision
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include "CalculatorDivision.h"

#define BUFSIZE 100

char buf[BUFSIZ];    //用于ungetch函数的缓冲区
int bufp = 0;        //buf中下一个空闲位置

int getch(void)//取一个字符(可能是压回的字符)
{
    return (bufp > 0) ? buf[--bufp] : getchar();//如果缓冲区没有字符再读,否则再次从输入中取数,如果缓冲区中有则从缓冲区读
}

void ungetchs(int c)//把字符压回到输入中
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
