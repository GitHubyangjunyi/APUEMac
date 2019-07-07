//
//  main.c
//  FibonacciDynamicProgramming
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

unsigned long Fibonacci(int n);
unsigned long FibonacciDynamicProgramming(int n);
unsigned long FibonacciIterative(unsigned long n);

int main(int argc, const char * argv[]) {
    
    for (int i = 0; i <= 100; i++)
    {
        printf("Fibonacci %d = %u\n", i, FibonacciDynamicProgramming(i));
    }
    
    printf("FibonacciIterative\n");
    
    for (int i = 0; i <= 60; i++)
    {
        printf("FibonacciIterative %d = %u\n", i, FibonacciIterative(i));
    }
    
    printf("Fibonacci\n");
    
    for (int i = 0; i <= 60; i++)
    {
        printf("Fibonacci %d = %u\n", i, Fibonacci(i));
    }
    
    
    
    return 0;
}

unsigned long Fibonacci(int n)//低效率递归版
{
    return (2 > n) ? n : Fibonacci(n - 1) + Fibonacci(n - 2);
}

unsigned long FibonacciDynamicProgramming(int n)//高效率动态规划版
{
    long f = 0;
    long g = 1;
    
    while (0 < n--)
    {
        g = g + f;
        f = g - f;
    }
    return g;
    //颠倒计算方向:由自顶向下递归改为自底向上迭代
}

unsigned long FibonacciIterative(unsigned long n)//迭代版
{
    unsigned long preVal = 1;
    unsigned long prePreVal = 0;
    if (n <= 2)
        return n;
    unsigned long loop = 1;
    unsigned long returnVal = 0;
    while (loop < n)
    {
        returnVal = preVal + prePreVal;
        //更新记录结果
        prePreVal = preVal;
        preVal = returnVal;
        loop++;
    }
    return returnVal;
}
