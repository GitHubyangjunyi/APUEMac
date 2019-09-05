//
//  main.c
//  SignPairDetection
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int brace;        //花括号
int brack;        //方括号
int paren;        //圆括号

void in_quote(int c);
void in_comment(void);
void search(int c);

int main(int argc, const char * argv[]) {

    int c;
    extern int brace;        //花括号
    extern int brack;        //方括号
    extern int paren;        //圆括号
    
    while ((c = getchar()) != EOF)
    {
        if (c == '/')
        {
            if ((c = getchar()) == '*')//连续碰到/*
                in_comment();//进入注释部分
            else
                search(c);//匹配当前符号
        }
        else if (c == '\'' || c == '"')//碰到单引号或者双引号,里面的内容无需配对
                in_quote(c);
            else
                search(c);//匹配当前符号
        //在搜索过程中三个取值是正数或者等于0都是合理的,但如果取值是负数,就表示有语法错误
        //比如连续出现3个[[[的情况是合法的,因为有可能在后面找到与之匹配的3个]]]
        //但要是出现3个连续的]]]使brack等于-3就不合法了,表明前面没有与这3个]]]匹配的[[[
        if (brace < 0)//必不可少,出现负数的特殊出错情况检查
        {
            printf("Unbalanced braces\n");
            brace = 0;
        }
        else if (brack < 0)
            {
                printf("Unbalanced brackets\n");
                brack = 0;
            }
            else if (paren < 0)
                {
                    printf("Unbalanced parentheses\n");
                    paren = 0;
                }
    }
    
    if (brace > 0)
        printf("Unbalanced braces\n");
    if (brack > 0)
        printf("Unbalanced brackets\n");
    if (paren > 0)
        printf("Unbalanced parentheses\n");
    
    return 0;
}

void in_quote(int c)
{
    int d;
    
    while ((d =getchar()) !=c)
        if (d == '\\')//碰到转义前缀跳过读取下一个
            getchar();
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

void search(int c)//功能:每遇到一个左花括号就递增brace,每遇到一个右花括号就递减brace,对brack和paren的处理也一样
{
    extern int brace;
    extern int brack;
    extern int paren;
    
    if (c == '{')
        ++brace;
    else if (c == '}')
            --brace;
        else if (c == '[')
                ++brack;
            else if (c == ']')
                    --brack;
                else if (c == '(')
                        ++paren;
                    else if (c == ')')
                        --paren;
}

//符号配对检测
//查找C语言中的基本语法错误,如符号不匹配的问题,要正确处理引号,包括单引号和双引号,转义字符序列与注释
//以上程序只对基本语法错误中的一部分进行检查:不配对的圆括号,方括号或花括号,其他语法错误不在检查范围内
//
//函数search的功能:每遇到一个左花括号就递增brace,每遇到一个右花括号就递减brace,对brack和paren的处理也一样
//在搜索过程中,如果变量brace,brack,paren的取值是正数或等于0的情况都是合法的,但如果取值是负数,就表示有语法错误
//比如连续出现3个[[[的情况是合法的,因为有可能在后面找到与之匹配的3个]]]
//但要是出现3个连续的]]]使brack等于-3就不合法了,表明前面没有与这3个]]]匹配的[[[
//如果有与之配对的3个[[[的话,变量brack应该等于0,因此while最后的判断语句必不可少,防止出现)( }}}{{{ ]][[
//主函数还将搜索并检查单引号和双引号以及注释标志的匹配情况,但对配对的标志之间的字符不做检查,因为注释或引号中的圆括号,方括号或花括号不要求配对出现
//
//在遇到EOF标记时,程序会对是否存在尚未匹配的圆括号,方括号或花括号进行最后的检查,如果存在括号不配对的情况,输出相应的错误信息
