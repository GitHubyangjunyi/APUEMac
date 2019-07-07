//
//  main.c
//  StructPointersMajor
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

struct pointer
{
    int x;
    int y;
};

int main(int argc, const char * argv[]) {
    
    //结构体的各类初始化方法
    
    struct pointer px1 =
    {
        .x = 1,
        .y = 2
    };
    printf("%d\n", px1.x);
    
    
    struct pointer px2 =
    {
        px2.x = 11,
        px2.y = 22
    };
    printf("%d\n", px2.x);
    
    struct pointer px3 =
    {
        px2.x = 111,
        px1.y = 200
    };
    //至此px3的初始化将会影响到px1和px2
    
    printf("%d\n", px2.y);
    
    struct pointer px4 = px1;//结构体赋值给结构体
    
    //来自指向结构的指针以及运算符->简化版
    struct pointer p;
    p.x = 10;
    p.y = 100;
    
    struct pointer *pp;
    pp = &p;
    
    printf("%d\n", (*pp).y);//首先就是对指针执行间接访问获得这个结构,然后使用点操作符来访问它的成员
    //printf("%d\n", sp.x);//这一行的写法是错误的,sp是结构体指针,要先进行间接访问取得结构,再用点操作符获取成员,这就导致了上一行写法的繁琐
    printf("%d\n", pp->x);//为解决繁琐而出现的方便的写法,直接访问,省去括号
    
    
    return 0;
}
