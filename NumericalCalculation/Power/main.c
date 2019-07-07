//
//  main.c
//  Power
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int power(int m, int n);//此函数原型中的参数名不要求与下面函数声明中的参数名相同,事实上参数名是可选的,可写成
//int power(int, int);//但合适的参数名可以提高可读性
int powers(int base, int n);

int main(int argc, const char * argv[]) {
    
    int i;
    printf("i    power(2, i)    powers(-3, i)\n");
    for ( i = 0; i <= 10; ++i)
    {
        printf("%d    %6d        %6d\n", i, power(2, i), powers(-3, i));
    }
    
    return 0;
}

int power(int base, int n)//计算整数base的n次幂,其中n >= 0,对函数调用power(2,5)来说,结果值为32
{
    int i, p;
    p = 1;
    
    for ( i = 1; i <= n; ++i)
        p = p * base;
    return p;
}

int powers(int base, int n)
{
    int p;
    
    for (p = 1; n > 0; --n)//powers函数内部对n的任何操作将不会影响到调用函数中n的原始参数值
        p = p * base;
    return p;
}

//int power(base, n)//早期C语言与ANSI C的区别
//int base, n;
//{
//    int i, p;
//    p = 1;
//
//    for (i = 1; i <= n; ++i)
//    {
//        p = p * base;
//    }
//    return p;
//}

//计算整数base的n次幂
