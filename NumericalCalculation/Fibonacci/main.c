//
//  main.c
//  Fibonacci
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

long fibonacci(long n);//递归计算斐波那契数列的第n项

int main(int argc, const char * argv[]) {
    

    for (int i = 1; i < 20; i++)
    {
        printf("%ld\n", fibonacci(i));
    }
    
    return 0;
}

long fibonacci(long n)
{
    if (n <= 1)
    {
        return    n;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

//斐波那契数列
