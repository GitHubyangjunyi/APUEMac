//
//  main.c
//  BitCount
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int bitcount(unsigned x);//声明为unsigned为了保证将x右移时,无论在什么机器上执行,左边空出位都用0补齐,而不是用符号位
int bitcountfast(unsigned x);

int main(int argc, const char * argv[]) {
    
    unsigned x = 9;
    
    printf("%d\n", bitcount(x));
    
    printf("%d\n", bitcountfast(x));
    
    return 0;
}

int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}

int bitcountfast(unsigned x)
{
    int b;
    for (b = 0; x != 0; x &= x - 1)
        ++b;
    return b;
}

//统计x中值为1的二进制位数
//x &= (x - 1)可以删除x中最右边值为1的一个二进制位
//
//( x - 1 ) + 1 = x
//x最右端为1的位于( x - 1 )在同一位置上为0的位是对应的,所以在一个采用对二的补码表示法的系统中,x & x - 1将清除x最右边值为1的位
//
//比如x=9    1001
//    1001
//    1000    AND    9 - 1 = 8
//    1000
//
//    1000
//    0111    AND    8 - 1 = 7
//    0000
//
//得出有两个1
//
//在最坏的情况下,即当x中的所有位都为1时,bitcountfast需要进行的AND操作次数与bitcount需要进行的移位次数一样多
//总的来说新方案bitcountfast比较快
