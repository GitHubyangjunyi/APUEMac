//
//  main.c
//  Typeof
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int f();

int main(int argc, const char * argv[]) {
    
    int i;
    typeof(i) j = 20;
    printf("%d\n", j);//20
    typeof(int *) a = &j;
    *a = 100;
    printf("%d\n", j);//100
    
    
    
    return 0;
}

int f()
{
    return 1;
}

//此小项目需在Linux环境下使用GCC编译运行
//typeof关键字是GNU C语言中的一个新扩展,这个特性在linux内核中应用非常广泛
//通过使用typeo可以获取一个变量或表达式的类型
//所以typeof的参数有两种形式:表达式/类型
//如果将typeof用于表达式则该表达式不会执行,只会得到该表达式的类型
//以下示例声明了int类型的var变量,因为表达式foo()是int类型的,由于表达式不会被执行,所以不会调用foo函数
//extern int foo();
//typeof(foo()) var;
//
//typeof(int) *y;        //定义int类型的指针y相当于int *y;
//typeof(int *) y;       //定义int类型的指针y相当于int *y;
//typeof(*x) y;          //定义一个指针x所指向类型的指针变量y
//typeof(int) y[4];      //相当于定义一个int y[4];
//typeof(*x) y[4];       //把y定义为指针x指向的数据类型的数组y
//typeof(typeof(char *)[4]) yc;//相当于定义字符指针数组char *yc[4];
//typeof(typeof (p)[4]) yy;    //相当于p类型的数组yy[4];
//
//局限性
//typeof构造中的类型名不能包含存储类说明符,extern或static,不过允许包含类型限定符,如const或volatile
//例如下列代码是无效的,因为它在typeof构造中声明了extern
//typeof(extern int) a;
