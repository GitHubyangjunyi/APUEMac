//
//  main.c
//  HighToLow
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int checkCPU(void);

int main(int argc, const char * argv[]) {
   
    unsigned int i = 0x12345678;
    printf("int %x,short %x\n", i, (short)i);
    
    if (checkCPU)
    {
        printf("小端模式");
    }
    else
    {
        printf("大端模式");
    }
    
    return 0;
}

int checkCPU(void)
{
    union MyUnion
    {
        int a;
        char b;
    }u;
    
    u.a = 1;
    //printf(u.b);//未初始化异常
    return (u.b == 1);
}

//编译器进行高精度向低精度的强制类型转换时丢弃高字节位,保留数值的低字节
//小端模式,数据的高字节存在高地址,低字节存在低地址,0x12345678    内存视图    7856    3412
//联合体Union的存放顺序是所有成员都从低地址开始存放
