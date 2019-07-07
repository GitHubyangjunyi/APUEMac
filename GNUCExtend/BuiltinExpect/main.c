//
//  main.c
//  BuiltinExpect
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int a;
    a = __builtin_expect(3, 1);
    printf("a = %d\n", a);
    
    a = __builtin_expect(3, 10);
    printf("a = %d\n", a);
    
    a = __builtin_expect(3, 100);
    printf("a = %d\n", a);
    
    return 0;
}

//运行结果如下
//a = 3
//a = 3
//a = 3
//
//内建函数__builtin_expect(exp, c)也常常用来编译优化,这个函数有两个参数,返回值就是其中一个参数,仍是exp
//这个函数的意义主要就是告诉编译器:参数exp的值为c的可能性很大,然后编译器可能就会根据这个提示信息做一些分支预测上的代码优化
//参数c跟这个函数的返回值无关,无论c为何值,函数的返回值都是exp
//
//现代CPU内部都有cache这个缓存器件,CPU的运行速度很高,而外部RAM的速度相对来说就低了不少
//所以当CPU从内存RAM读写数据时就会有一定的性能瓶颈,为了提高程序执行效率,CPU都会通过cache这个CPU内部缓冲区来缓存一定的指令或数据
//CPU读写内存RAM中的数据时,会先到cache里面去看看能不能找到,找到的话就直接进行读写,找不到的话cache会重新缓存一部分内存数据进来
//CPU读写cache的速度远远大于内存RAM,所以通过这种方式可以提高系统的性能
//那cache如何缓存内存数据呢?简单来说就是依据空间相近原则,比如CPU正在执行一条指令,那么下一个指令周期,CPU就会大概率执行当前指令的下一条指令
//如果此时cache将下面几条指令都缓存到cache里面,下一个指令周期CPU就可以直接到cache里取指/翻译/执行,从而使运算效率大大提高
//但有时候也会出现意外,比如程序在执行过程中遇到函数调用/if分支/goto跳转等程序结构会跳到其它地址执行,那么缓存到cache中的指令就不是CPU要获取的指令
//此时我们就说cache没有命中,cache会重新缓存正确的指令代码给CPU读取,这就是cache工作的基本流程
//我们在编写程序时遇到if/switch这种选择分支的程序结构,可以将大概率发生的分支写在前面,这样程序运行时,因为大概率发生,所以大部分时间就不需要跳转
//程序就相当于一个顺序结构,从而提高cache的命中率,内核中已经实现一些相关的宏,如likely和unlikely用来提醒程序员优化程序
