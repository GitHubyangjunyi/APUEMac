//
//  main.c
//  StackRecursion
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int iterate(int value);
int sum;

int main(int argc, const char * argv[]) {
    
    int v = iterate(4);
    
    printf("%d\n", v);
    
    
    return 0;
}

int iterate(int value)
{
    if (value == 1)
    {
        return true;
    }
    return sum = value + iterate(value - 1);
}
