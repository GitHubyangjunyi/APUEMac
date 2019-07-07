//
//  main.c
//  Rightrot
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

unsigned rightrot(unsigned x, int n);
int wordlength(void);

int main(int argc, const char * argv[]) {
    
    unsigned x = 9;
    printf("%u\n", (unsigned)rightrot(x, 4));
    
    return 0;
}

unsigned rightrot(unsigned x, int n)//首先利用变量rbit把x最右端的位左移到最左端的位置(wordlength() - 1)
{                                    //然后把x右移一位再对右移后的x与rbit进行OR操作,就完成了一次对x的循环右移操作
    int wordlength(void);
    int rbit;
    
    while (n-- >0)
    {
        rbit = (x & 1) << (wordlength() - 1);
        x = x >> 1;
        x = x | rbit;
    }
    
    return x;
}

int wordlength(void)//计算出计算机所使用的字长
{
    int i;
    unsigned v = (unsigned)~0;
    for (i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}

//返回将x循环右移n位后得到的值
