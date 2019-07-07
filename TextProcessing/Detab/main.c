//
//  main.c
//  Detab
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define TABINC 8    //假设每8个位置就会出现一个制表位

int main(int argc, const char * argv[]) {
    
    int c, nb;
    int pos;    //程序在文本行中的位置
    nb = 0;
    pos = 1;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            nb = TABINC - (pos - 1) % TABINC;//当遇到制表符时,程序要计算出到达下一个制表位需要的空格数nb,(pos - 1) % TABINC先计算
            while (nb > 0)
            {
                putchar(' ');
                ++pos;
                --nb;
            }
        }
        else if (c == '\n')//如果遇到换行符,打印换行符并把pos重新初始化为输入行的第一字符位置
        {
            putchar(c);
            pos = 1;
        }
        else//如果遇到的是其他字符,打印并递增pos的值
        {
            putchar(c);
            ++pos;
        }
    }
    
    
    return 0;
}

//将输入中的制表符替换成适当数目的空格,使空格充满到下一个制表符终止的地方(扩展练习5-11和5-12)
//假设制表符终止位的位置是固定的,比如每隔n列就会出现一个制表符终止位
