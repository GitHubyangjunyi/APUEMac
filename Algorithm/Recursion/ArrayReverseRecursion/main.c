//
//  main.c
//  ArrayReverseRecursion
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void ArrayReverseRecursion(int a[], int low, int high);
void Swap(int a[], int b[]);

int main(int argc, const char * argv[]) {
    
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    
    ArrayReverseRecursion(a, 0, 9);
    
    
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", a[i]);
    }
    
    
    
    
    return 0;
}

void ArrayReverseRecursion(int *a, int low, int high)
{
    if (low<high)
    {
        Swap(a[low], a[high]);
        ArrayReverseRecursion(a, low + 1, high - 1);
    }
    else
    {
        return;
    }
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
