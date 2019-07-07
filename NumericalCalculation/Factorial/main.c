//
//  main.c
//  Factorial
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

long factorial(int n);
long factorials(int n);

int main(int argc, const char * argv[]) {
   
    
    printf("%ld\n", factorial(5));
    printf("%ld\n", factorials(5));
    printf("%ld\n", factorials(10));
    
    printf("%ld\n", factorials(0));
    printf("%ld\n", factorials(1));
    printf("%ld\n", factorials(-1));
    
    
    return 0;
}

long factorial(int n)
{
    int i;
    long t = 1;
    if (n < 0)
        return -1;
    for ( i = 1; i <= n; i++)
    {
        t = t * i;
    }
    return t;
}

long factorials(int n)
{
    long t = 1;
    if (n < 0)
        return -1;
    for (; n > 0; n--)
    {
        t = t * n;
    }
    return t;
}

