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
    //int d;
    
    while ((c = getchar()) != EOF)
        rcomment(c);
    
    return 0;
}

void rcomment(int c)//rcomment搜索注释语句的起始标志/*,在找到这个标志时,将调用另一个函数in_comment搜索注释语句的结束标志*/,从而确保注释都能够被删除
{                   //rcomment还将搜索单引号和双引号,在找到它们时,调用echo_quote,echo_quote的参数将指明找到的字符是一个单引号还是双引号
    int d;         //echo_quote确保引号中的内容能够按原样输出,echo_quote不会把跟在一个反斜杠后面的引号看作是结束引号
    
    if (c == '/')//如果碰到/
        if ((d = getchar()) == '*')//如果在碰到/的情况下再次碰到*则调用in_comment()进入注释
            in_comment();//清除完注释回到main函数进入下一轮while
        else if (d == '/')//如果是//则输出/并将第二个/作为参数调用rcomment()进入下一轮
            {
                putchar(c);
                rcomment(d);
            }
            else//否则就不是注释直接输出两者
            {
                putchar(c);
                putchar(d);
            }
    //'\''这是一个单引号
    else if(c == '\'' || c == '"')//比如碰到"调用echo_quote()并且
            echo_quote(c);
        else//不是注释的情况
            putchar(c);
}

void in_comment(void)
{
    int c = getchar();
    int d = getchar();
    
    while (c != '*' || d != '/')//当未出现*/则一直前进,除非出现*/,否则一直循环
    {
        c = d;          //c等于d,d等于下一个字符,相当于移动一次双标志位
        d = getchar();
    }
}

void echo_quote(int c)//echo_quote确保引号中的内容能够按原样输出,echo_quote不会把跟在一个反斜杠后面的引号看作是结束引号
{
    int d;
    
    putchar(c);//先输出'或者"
    while ((d = getchar()) != c)//比如以"为参数调用该函数就得在再次碰到"之前一直输出字符并且忽略转义的\
    {
        putchar(d);
        if (d == '\\')//转义序列\跳过
            putchar(getchar());
    }
    putchar(d);
}

//功能是删除注释,要正确处理带引号的字符和字符串常量,在C语言程序中,注释不允许嵌套/*/**/*/
///*/**/*/
//这里说的注释的形式应该是/*xx*/这种形式的而不是//
//这个程序假定输入是一个合法的C程序
