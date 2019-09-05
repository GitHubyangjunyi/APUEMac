//
//  main.c
//  Setbits
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(int argc, const char * argv[]) {
    
    unsigned x = 255;//11111111
    printf("%d\n", setbits(x, 4, 4, 4));//00000100
    //1110 1001
    
    
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return x & ~(~(~0 << n) << (p + 1 - n)) |
    (y & ~(~0 << n)) << (p + 1 - n);
}

//返回对x执行下列操作后的结果值:将x中从第p位开始的n个位设置为y中最右边n位的值,x的其余各位保持不变
//
//为了把x中的n位设置为y最右边n位的值
//    xxxx...xnnnx...xxx
//    yyy...........ynnn
//
//需要对x中的n位清零,把y中除了最右边的n位以外的其他位都清零并左移到p位处,然后执行OR操作
//
//    xxxx...x000x...xxx
//    000.....nnn....000    OR
//
//    xxxx...xnnnx...xxx
//
//为了对x中的n位清零,需要把x与一个屏蔽码进行AND操作,这个屏蔽码从p位置开始的n位都是0,其他位则全为1
//首先把一个所有位都为1的屏蔽码左移n位,在它的最右边制造出n位0
//    ~0 << n
//然后把屏蔽码最右边的n位设置为1,把其余位全部设置为0
//    (~(~0 << n)
//接下来把屏蔽码最右边的n个为1的位左移到第p处
//    (~(~0 << n) << (p + 1 - n))
//在往后把屏蔽码从第p位开始的n位设置为0,其余全部设置为1
//    ~(~(~0 << n) << (p + 1 - n))
//用这个屏蔽码与x进行AND操作,就完成了对x从第p位开始的n位清零工作
//    x & ~(~(~0 << n) << (p + 1 - n))
//
//为了把y中除了最右端的n位以外的所有位清零,需要用最右端的n位全为1,其余位全为0的屏蔽码对y进行AND操作,选出y最右端的n位
//    (y & ~(~0 << n))
//把这n位左移到位置p处
//    (y & ~(~0 << n)) << (p + 1 - n)
//
//最后进行OR操作合并
