//
//  main.c
//  FoldLine
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXCOL 10//输入行的折行位置,即输入行的第n列
#define TABINC 8

char line[MAXCOL];

int exptab(int pos);
int findblnk(int pos);
int newpos(int pos);
void printl(int pos);

int main(int argc, const char * argv[]) {
    
    int c;
    int pos;//程序在文本行中的当前位置,程序将在输入行的每一处第n列之前对该输入行折行
    
    pos = 0;
    while ((c = getchar()) != EOF)
    {
        line[pos] = c;
        if (c == '\t')
            pos = exptab(pos);
        else if (c == '\n')
        {
            printl(pos);
            pos = 0;
        }
        else if (++pos >= MAXCOL)
        {
            pos = findblnk(pos);
            printl(pos);
            pos = newpos(pos);
        }
    }
    
    
    return 0;
}

int exptab(int pos)
{
    line[pos] = ' ';
    for ( ++pos; pos < MAXCOL && pos % TABINC != 0; ++pos)
        line[pos] = ' ';
    if (pos < MAXCOL)
        return pos;
    else
    {
        printl(pos);
        return 0;
    }
}

int findblnk(int pos)//从输入行的pos处开始倒退着寻找一个空格,目的是为了保持折行位置的单词的完整
{                    //如果找到一个空格就返回紧跟在该空格符后面的那个位置的下标,如果没有找到空格,返回MAXCOL
    while (pos > 0 && line[pos] != ' ')
        --pos;
    if (pos == 0)
        return MAXCOL;
    else
        return pos+1;
}

int newpos(int pos)//调整输入行,将把从位置pos开始的字符复制到下一个输出行的开始,再返回pos的值
{
    int i, j;
    if (pos <= 0 || pos >= MAXCOL)
        return 0;
    else
    {
        i = 0;
        for ( j = pos; j < MAXCOL; ++j)
        {
            line[i] = line[j];
            ++i;
        }
        return i;
    }
}

void printl(int pos)//打印输出从位置零到位置pos-1之间的字符
{
    int i;
    for ( i = 0; i < pos; ++i)
    {
        putchar(line[i]);
    }
    if (pos > 0)
    {
        putchar('\n');
    }
}

//将较长的输入行折成短一些的两行或多行,折行的位置在输入行的第n列之前的最后一个非空格字符之后
//要保证程序能够智能地处理输入行很长以及在指定的列前没有空格或制表符的情况
//
//这个程序将制表符扩展为空格
//每遇到一个换行符就把此前的输入文本打印出来
//每当变量pos的值达到MAXCOL时,就会对输入行进行折叠
