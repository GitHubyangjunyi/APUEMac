//
//  main.c
//  Builtin
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void f(void)
{
    int *p;
    p = __builtin_return_address(0);
    printf("f    return address: %p\n", p);
    p = __builtin_return_address(1);;
    printf("func return address: %p\n", p);
    p = __builtin_return_address(2);;
    printf("main return address: %p\n", p);
    printf("\n");
}

void func(void)
{
    int *p;
    p = __builtin_return_address(0);
    printf("func return address: %p\n", p);
    p = __builtin_return_address(1);;
    printf("main return address: %p\n", p);
    printf("\n");
    f();
}

int main(int argc, const char * argv[]) {
    
    int *p;
    p = __builtin_return_address(0);
    printf("main return address: %p\n", p);
    printf("\n");
    func();
    printf("goodbye!\n");
    
    return 0;
}

//内建函数,顾名思义就是编译器内部实现的函数,这些函数跟关键字一样可以直接使用,无须像标准库函数那样要#include对应的头文件才能使用
//内建函数的函数命名,通常以__builtin开头,这些函数主要在编译器内部使用,主要是为编译器服务的,内建函数的主要用途如下
//    用来处理变长参数列表
//    用来处理程序运行异常
//    程序的编译优化/性能优化
//    查看函数运行中的底层信息/堆栈信息等
//    C标准库函数的内建版本
//
//C语言函数在调用过程中会将当前函数的返回地址和寄存器等现场信息保存在堆栈中,然后才会跳到被调用函数中去执行
//当被调用函数执行结束后,根据保存在堆栈中的返回地址,就可以直接返回到原来的函数中继续执行
//在这个程序中main()函数调用func()函数,在main()函数跳转到func()函数执行之前会将程序正在运行的当前语句的下一条语句,如下代码所示,的地址保存到堆栈中
//    printf("goodbye!\n");
//然后才去执行func();这条语句跳到func()函数去执行,func()执行完毕后如何返回到main()函数呢?
//很简单,将保存到堆栈中的返回地址赋值给PC指针就可以直接返回到main()函数继续往下执行了
//每一层函数调用都会将当前函数的下一条指令地址,即返回地址压入堆栈保存,各层函数调用就构成 了一个函数调用链,在各层函数内部
//我们使用内建函数就可以打印这个调用链上各个函数的返回地址,程序的运行结果如下
//
//main return address: 0040124B

//func return address: 004013C3
//main return address: 0040124B

//f    return address: 00401385
//func return address: 004013C3
//main return address: 0040124B
