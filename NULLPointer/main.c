//
//  main.c
//  NULLPointer
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
   
    int *p = NULL;
    if (!p)
    {
        printf("hello, world\n");
    }
    
    if (p == 0)
    {
        printf("hello, world\n");
    }
    
    
    return 0;
}

//空指针的逻辑取反操作
//从intel汇编来看,我觉得这是历史遗留的原因
//在早期的编译器中if(!p)和if(p != NULL)编译出来是有区别的
//前者是test指令,本质上是自身与运算的同时改变状态寄存器
//后者是cmp指令,比较指令不单是对0的判断
//虽然两者的性能一致,区别只是前者的指令长度更短,很早以前的内存是很值钱的
//所以为了能够尽可能的节约内存成本,应该设计一种方式使代码能利用到test指令
//这应该就是if(!p)与if(p)诞生的原因了
