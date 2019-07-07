//
//  main.c
//  DanglingPointerThree
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define RAII_VARIABLE(vartype, varname, initval, dtor) \
        void _dtor_ ## varname (vartype * v) { dtor(*v); } \
        vartype varname __attribute__((cleanup(_dtor_ ## varname))) = (initval)

void foo(void);
void RAIIExample();

int main(int argc, const char * argv[]) {
    
    int *pi;//可以是局部变量也可以是全局变量
    {
        int temp = 5;
        pi = &temp;
    }
    
    *pi = 100;//此时变成迷途指针
    printf("%d\n", *pi);
    
    foo();
    
    //RAII_VARIABLE宏
    
    
    
    return 0;
}

void foo(void)
{
    //...覆盖掉temp
}

void RAIIExample()
{
    /*RAII_VARIABLE(char*, name, (char*)malloc(32), free);
     strcpy(name, "RAII Example");
     printf("%s\n", name);*/
}


//使用块语句产生的迷途指针
//大部分编译器将块语句当做一个栈帧,temp变量分配与栈帧上,之后在块语句退出后出栈
//pi指针现在指向一块最终可能被其他活跃记录覆盖的内存区域,比如foo()函数
//
//迷途指针处理
//1.释放指针后置为NULL,后续使用这个指针会终止程序,但如果存在多个指针还是会有问题,因为赋值只会影响一个指针
//2.写一个特殊函数替代free
//3.有些运行时或调试系统会在释放后覆写数据,取决于被释放的对象,Visual Studio会用0xCC/CD/DD
//    在不抛出异常的情况下,如果程序员在预期之外的地方看到这些值则可认为程序可能在访问已经释放的值
//4.使用第三方工具
//
//微软提供了解决动态分配内存的覆写和内存泄漏的技术,这种方法在调试版程序中用了特殊的内存管理技术
//1.检查堆的完整性
//2.检查内存泄漏
//3.模拟堆内存不够的情况
//微软是通过一个特殊的数据结构管理内存分配来做到这一点的,这种结构维护着调试信息,比如malloc调用点的文件名和行号
//还会在实际的内存分配之前和之后分配缓冲区来检测对实际内存的覆写
//
//堆管理器分配内存在不同的编译器有不同的实现,大部分堆管理器把堆或数据段作为内存资源,这种方法的缺点是会造成碎片
//而且可能与程序的栈碰撞,堆管理器需要处理很多问题,比如堆是否基于线程或进程分配,如何保护堆不受攻击
//
//内存不再使用之后会被收集起来以备后续使用,释放的内存称为垃圾,因此垃圾回收就是指这一过程
//鉴于以下原因,垃圾回收有如下价值
//1.不需要程序员费尽心思决定何时释放内存
//2.让程序员专注于应用程序本身的问题
//
//资源获取即初始化(Resource Acquisition Is Initialization, RAII)是Bjarne Stroustrup发明的技术,可以用来解决C++中的资源分配和释放
//即使有异常发生,这种技术也能保证资源的初始化和后续的释放,分配的资源最终总是能得到释放
//有好几种方式可以在C中使用RAII,GNU编译器提供了非标准的扩展来支持这个特性,一旦变量超出作用域会自动触发释放过程
//GNU扩展要用到RAII_VARIABLE宏,它声明一个变量,然后给变量关联如下属性
//1.一个类型
//2.创建变量时执行的函数
//3.变量超出作用域时执行的函数
//这个宏如下所示
//#define RAII_VARIABLE(vartype, varname, initval, dtor) void _dtor_ ## varname(vartype * v) { dtor(*v); } vartype varname __attribute__((cleanup(_dtor_ ## varname))) = (initval)
