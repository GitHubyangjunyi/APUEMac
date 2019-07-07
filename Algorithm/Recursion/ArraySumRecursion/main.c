//
//  main.c
//  ArraySumRecursion
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int ArraySumRecursion(int a[], int n);

int main(int argc, const char * argv[]) {
    
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int sum = 0;
    for (size_t i = 0; i < 10; i++)
    {
        sum = sum + a[i];
    }
    printf("sum=%d\n", sum);
    
    sum = 0;
    sum = ArraySumRecursion(a, 10);
    printf("ArraySumRecursion sum=%d\n", sum);
    
    
    
    
    return 0;
}

int ArraySumRecursion(int a[], int n)
{
    return (n < 1) ? 0 : ArraySumRecursion(a, n - 1) + a[n - 1];
}

//复杂度分析
//递推方程
//T(n)=T(n-1)+O(1)
//T(0)=O(1)
//T(n)-n=T(n-1)-(n-1)
//        =T(2)-2
//        =T(1)-1
//        =T(0)
//T(n)=O(1)+n=O(n)
