//
//  main.c
//  CharClassifiedStatistics
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int c, i;
    int nwhite;//空白字符
    int nother;//其他字符
    int ndigit[10];//各个数字
    
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)//1.初始化数组为全0
    {
        ndigit[i] = 0;
    }
    
    while ((c = getchar()) != EOF)
    {
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];//2.如果是数字则对应的数组下标是c-'0'(整型表达式)
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;//3.如果是空白符
        else
            ++nother;//4.其他字符
    }
    
    printf("digits =");
    for ( i = 0; i < 10; ++i)
    {
        printf(" %d", ndigit[i]);
    }
    printf(", white space = %d, other = %d\n",
           nwhite, nother);
    
    
    
    return 0;
}

//字符分类统计
//统计各个数字,空白符及其他字符出现的次数
