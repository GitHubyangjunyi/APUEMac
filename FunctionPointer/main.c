//
//  main.c
//  FunctionPointer
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int add(int a, int b);
int reduce(int a, int b);
int(*func(int x))();
//先从最下面开始看
int(*FP)(int a, int b);
//每次都像上面那样定义很麻烦,下面是改进版
typedef int(*PF)(int, int);
//定义int(int, int)类型函数的指针(*PF)

int main(int argc, const char * argv[]) {
   
    FP = add;
    printf("add:%d\n", FP(3, 4));
    
    PF pfunc = NULL;
    pfunc = reduce;
    printf("reduce:%d\n", pfunc(3, 4));
    
    
    return 0;
}

int add(int a, int b)
{
    return a + b;
}

int reduce(int a, int b)
{
    return a - b;
}

int(*func(int x))()//func函数返回一个函数指针,且带有一个int参数,该返回的函数指针类型为int()
{
    return NULL;
}

//来自CPlusPlus的小项目FunctionPointers
//一个运行中的程序在内存中的布局分为四个区域,代码区/全局数据区/堆区/栈区
//指向数据区的指针称为数据指针,指向代码区域的指针称为指向函数的指针,简称为函数指针
//但要注意,与返回指针类型的函数不同,该函数称为指针函数
//int* f(int a);
//char* copy(char* s1,char* s2);
//f函数返回int指针,即为int指针函数,copy函数称为char指针函数
//运行中的程序,其函数都存放在代码区,每个函数都有起始地址,指向函数起始地址的指针完全不同于数据指针
//之间不能相互转换,通过函数指针可以调用所指向的函数
//int m(int,int);
//函数是以参数个数/参数类型/参数顺序甚至返回值类型来区分不同类型的
//函数的类型表示是函数声明去掉函数名,所以上面的m函数类型表示为int(int,int)
//声明一个int(int)型函数就是把函数名放在返回值与括号之间
//int g(int);
//同样,定义一个int(int)型函数指针gp就是将指针名放在返回类型和括号之间
//int (*gp) (int);
//上面是定义一个函数指针,不是声明,而且函数指针名的括号不能省,表示*gp是一个整体
//int *gp (int);表示声明一个含有一个整型参数的整型指针函数,等价于int* gp
//定义函数指针还可以直接初始化
//int g(int);
//int (*gp)(int)=g;
//或者int (*gp)(int);
//gp=g;
//定义了一个函数指针,就拥有了一个指针实体,实体大小跟int类型实体大小一样
//函数指针的类型必须接受编译器类型检查,gp指针所指向的函数拥有一个int型参数,并返回int值
//函数指针也是一种数据类型,即
//int (*) (int);
//是int(int)型函数的指针类型,其中(*)的括号不能省,因为是数据类型就可以作为函数参数
//void f(int* a,int* b,int (*) (int));
//函数指针的定义比较复杂,可以使用typedef简化
//typedef int (*Fun)(int a,int b);
//int m(int,int);
//Fun funp=m;
//简略形式的函数指针表示
//int();//无名函数声明,表示一个函数类型
//int func();//函数声明,表示一个函数类型
//int (*) ();//无名函数指针
//int (*fp) ();//函数指针定义,fp是函数指针名,函数指针的函数类型是int()
//也就是说如果
//typedef int Func();//表示将该函数类型称之为Func
//则函数指针定义等价为
//Func* pf;
//进一步地
//int(*func(int)) ();//是一个函数声明,是int()类型的指针函数,名字为func
//或者基于Func函数类型名字,可写为
//Func* func(int);
//func函数返回一个函数指针,且带有一个int参数,该返回的函数指针类型为int()
