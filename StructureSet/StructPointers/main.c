//
//  main.c
//  StructPointers
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define LEN 20

struct names
{
    char first[LEN];
    char last[LEN];
};

struct guy//占用84字节
{
    struct names handle;
    char favfood[LEN];
    char job[LEN];
    float income;
};

int main(int argc, const char * argv[]) {
    
    //创建结构数组
    struct guy fellow[2] =
    {
        {
            {"Ewen","Villard"},
            "grilled salmon",
            "personality coach",
            68112.00
        },
        
        {
            {"Rodney","Swillbelly"},
            "tripe",
            "tabloid editor",
            432400.00
        }
    };
    
    struct guy * him;//指向结构的指针
    him = &fellow[0];
    
    printf("address #1:%p #2:%p\n", &fellow[0], &fellow[1]);
    
    printf("pointer #1:%p #2:%p\n", him, him + 1);
    
    printf("him->income is $%.2f:  (*him).income is $%.2f\n", him->income, (*him).income);
    
    printf("(him+1)->income is $%.2f:  (*(him + 1)).income is $%.2f\n", (him+1)->income, (*(him + 1)).income);
    
    him++;//指向下一个结构
    
    printf("him->favfood is %s:  him->handle.last is %s\n", him->favfood, him->handle.last);
    
    
    return 0;
}

//如果barney是一个guy类型的结构,可以这样写
//    him=&barbey;
//和数组不同,结构名并不是结构的地址
//如何通过him获得fellow[0]的成员值?
//1.使用->运算符
//如果him==&barney,那么him->income即是barney.income
//如果him==&fellow[0],那么him->income即是fellow[0].income
//换句话说,->运算符后面的结构指针和.运算符后面的结构名工作方式相同(不能写成him.income,因为him不是结构名)
//him只一个指针,但是him->income是该指针所指向结构的一个成员,所以him->income是一个float类型的变量
//
//2.fellow[0].income==(*him).income        必须使用圆括号,因为.的优先级比*号高
//总之,如果him是指向guy类型结构barney的指针,下列关系恒成立
//    barney.income == (*him).income == him->income    //假设 him == &barney
