//
//  main.c
//  UnionType
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    union
    {
        float   fuel_load;//4字节
        char a[5];        //5字节
        int   pallets;    //4字节
    }fighter;            //因此联合体空间为8
    
    union
    {
        int i;
        char x[2];
    }a;
    
    a.x[0] = 10;//0000 1010
    a.x[1] = 1;    //0000 0001
    printf("a.x[0] = %d\n", a.x[0]);
    printf("a.i = %d\n", a.i);
    printf("sizeof(a) = %d\n", sizeof(a));
    
    
    return 0;
}

//联合体union的定义方式与结构体一样,但二者有根本区别
//在结构中各成员有各自的内存空间,一个结构变量的总长度是各成员长度之和
//而在联合中,各成员共享一段内存空间,一个联合变量的长度等于各成员中最长的长度
//联合体长度
//在The C Programming Language里面讲述union内存分配的原话是
//1.联合体就是一个结构
//2.联合体的所有成员相对于基地址的偏移量为0
//3.此结构空间要大到总够容纳最宽的成员
//4.并且其对齐方式要适合于联合体中所有类型的成员
