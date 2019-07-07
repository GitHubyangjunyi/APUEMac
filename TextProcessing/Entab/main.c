//
//  main.c
//  Entab
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define TABINC 8    //假设每8个位置就会出现一个制表位

int main(int argc, const char * argv[]) {
    
    int c;
    int nb;     //替换空格串的空格的最少个数
    int nt;     //替换空格串的制表符的最少个数
    int pos;    //程序在文本行中的位置
    
    nb = 0;     //1.初始化空格制表符都为0
    nt = 0;
    for ( pos = 1; (c = getchar()) != EOF; ++pos)
        if (c == ' ')//2.如果遇到空格
        {
            if (pos % TABINC != 0)//3.当前光标位置不是TABIINC能整除的,空格数加一
                ++nb;
            else//4.如果能整除,那么清零累积空格数,制表符数加一
            {
                nb = 0;
                ++nt;
            }
        }
        else//5.不是空格符的情况
        {
            for ( ; nt > 0; --nt)    //6.先将累积的制表符打印出来
                putchar('\t');
            if (c == '\t')          //7.如果遇到制表符,清零空格数,准备打印这个制表符
                nb = 0;
            else                    //8.如果不是空格也不是制表符,将累积空格输出
                for (; nb > 0; --nb)
                    putchar(' ');
            putchar(c);            //9.制表符或普通字符,则输出
            if (c == '\n')         //10.遇到换行符,清零pos
                pos = 0;
            else if (c == '\t')   //11.如果是制表符,刚才输出制表符了,重新计算pos位置
                pos = pos + (TABINC - (pos - 1) % TABINC) - 1;
        }
    
    
    return 0;
}

//将空格串替换为最少数量的制表符和空格,但要保持单词之间的间隔不变(扩展练习5-11和5-12)
//假设制表符终止位的位置是固定的,比如每隔n列就会出现一个制表符终止位
//
//程序的主要想法是找出全部空格
//变量pos每递增到TABINC的一个倍数时,就要把空格串替换成一个制表符
//当遇到一个非空格符时,程序先把遇到这个字符之前积累起来的制表符和空格打印出来,再把这个字符打印出来
//然后程序将nb和nt设置为0,如果当前字符是一个换行符,还要把变量pos重新设置为输入行的开始
//当遇到一个制表符时,程序将只把此前积累的制表符和当前遇到的这个制表符打印出来
//如果只需一个空格就能到达下一个制表位,选择把它替换成为一个制表符,这有助于避免特殊情况
