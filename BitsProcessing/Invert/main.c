//
//  main.c
//  Invert
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(int argc, const char * argv[]) {
    
    unsigned x = 9;                 //0000 1001
    printf("%d\n", invert(x, 4, 3));//0001 0101
    
    unsigned y = 9;                 //0000 1001
    printf("%d\n", invert(y, 4, 2));//0001 0001
    
    
    
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return x ^ (~(~0 << n) << (p + 1 - n));
}

//返回对x执行下列操作后的结果值:将x中从第p位开始的n个位求反,x的其余各位保持不变
//首先把一个所有位都为1的屏蔽码左移n位,在它的最右边制造出n位0
//    (~0 << n)
//然后把屏蔽码最右边的n位设置为1,其余位设置为0
//    (~(~0 << n)
//接下来把屏蔽码最右边的n个为1的位左移到第p位处
//    (~(~0 << n) << (p + 1 - n))
//将屏蔽码与x异或
