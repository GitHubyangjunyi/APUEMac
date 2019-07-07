//
//  main.c
//  Polynomial
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define N 5

float evaluate(float coef[], float x, int n)//空间复杂度为O(n)
{
    float f;
    int A[N], i;
    for (A[0] = 1, i = 1; i < n; i++)
    {
        A[i] = x * A[i - 1];
    }
    //A[O] = 1
    //A[1] = x * 1
    //A[2] = x * A[1] = xx
    //A[3] = x * A[2] = xxx
    
    for (f=0, i = 0; i < n; i++)
    {
        f = f + coef[i] * A[i];//系数coef[i]乘上幂A[i]等于对应项
    }
    return f;
}

float evaluatex(float coef[], float x, int n)//书上原版比如数组有4个元素则n传入3,空间复杂度为O(1)
{
    float f;
    int i;
    for (f = coef[n], i = n - 1; i >= 0; i--)//从f()最后一项开始反向处理乘上x
    {
        f = f * x + coef[i];//系数coef[i]    幂A[i]
    }
    return f;
}

float evaluatefix(float coef[], float x, int n)//修正版比如数组有4个元素则n传入4,空间复杂度为O(1)
{
    float f;
    int i;
    for (f = coef[n - 1], i = n - 2; i >= 0; i--)//从f()最后一项开始反向处理乘上x
    {
        f = f * x + coef[i];//系数coef[i]    幂A[i]
    }
    return f;
}

int main(int argc, const char * argv[]) {
    
    float coef[4] = { 1,2,3,4 };
    float f = evaluate(coef, 2, 4);
    
    printf("%f\n", f);
    
    f = evaluatex(coef, 2, 3);
    
    printf("%f\n", f);
    
    f = evaluatefix(coef, 2, 4);
    
    printf("%f\n", f);
    
    
    return 0;
}

//多项式计算
//a0 + a1x + a2xx + a3xxx + an-1xn-1
