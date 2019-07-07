//
//  main.c
//  Getbits
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main(int argc, const char * argv[]) {
    
    unsigned x = 9;
    printf("%d\n", getbits(x, 4, 3));
    
    
    return 0;
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n))&~(~0 << n);
}

//返回x中从第p位开始的n位
//假定最右边的一位是第0位,getbits(x,4,3)返回第4,3,2位
//    x >> (p + 1 - n)将期望获得的字段移位到字的最右端
//
//    ~(~0 << n)建立最右边n位全是1的屏蔽码
