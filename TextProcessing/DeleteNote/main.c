//
//  main.c
//  DeleteNote
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void rcomment(int c);
void in_comment(void);
void echo_quote(int c);

int main(int argc, const char * argv[]) {
    
    int c;
    int d;
    
    while ((c = getchar()) != EOF)
        rcomment(c);
    
    
    
    return 0;
}

void rcomment(int c)//rcomment搜索注释语句的起始标志/*,在找到这个标志时,将调用另一个函数in_comment搜索注释语句的结束标志*/,从而确保注释都能够被删除
{                    //rcomment还将搜索单引号和双引号,在找到它们时,调用echo_quote,echo_quote的参数将指明找到的字符是一个单引号还是双引号
    int d;            //echo_quote确保引号中的内容能够按原样输出,echo_quote不会把跟在一个反斜杠后面的引号看作是结束引号
    
    if (c == '/')
        if ((d = getchar()) == '*')
            in_comment();
        else if (d == '/')
        {
            putchar(c);
            rcomment(d);
        }
        else
        {
            putchar(c);
            putchar(d);
        }
        else if(c == '\'' || c == '"')
            echo_quote(c);
        else
            putchar(c);
}

void in_comment(void)
{
    int c = getchar();
    int d = getchar();
    
    while (c != '*' || d != '/')
    {
        c = d;
        d = getchar();
    }
}

void echo_quote(int c)
{
    int d;
    
    putchar(c);
    while ((d = getchar()) != c)
    {
        putchar(d);
        if (d == '\\')
            putchar(getchar());
    }
    putchar(d);
}

//功能是删除注释,要正确处理带引号的字符和字符串常量,在C语言程序中,注释不允许嵌套
//
//这个程序假定输入是一个合法的C程序
