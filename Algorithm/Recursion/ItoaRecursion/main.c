//
//  main.c
//  ItoaRecursion
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <math.h>

void itoarecursion(int n, char s[]);

int main(int argc, const char * argv[]) {
    
    char s[] = "";
    
    itoarecursion(12, s);
    printf("%s\n", s);
    
    itoarecursion(-125, s);
    printf("%s\n", s);
    
    
    
    return 0;
}

void itoarecursion(int n, char s[])
{
    static int i;
    
    if (n / 10)
        itoarecursion(n / 10, s);
    else
    {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }
    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}

//递归版本的reverse函数,将字符串s倒置
//itoarecursion函数需要两个参数,一个是将被转换为字符串的整数n,一个是用来保存结果的字符数组s
//如果整除n / 10不为零九江以整数n / 10为参数调用自身
//如果n / 10在某次递归调用中结果为零,就得到n的最高位数字,用一个static变量作为数组s的索引,如果n是一个负数,就在字符数组的第一个位置上放上一个符号并对i递增
//因为itoarecursion是递归性的,所以它将按从左到右的顺序计算出整数n的每一位数字,需要注意的是:每次递归调用都将用一个"\0"字符来结束字符数组s
//但下一次递归调用时,除了最后一次将覆盖掉这个"\0"字符
