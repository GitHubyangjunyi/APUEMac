//
//  main.c
//  BuiltinConstantp
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define _dma_cache_sync(addr, sz, dir)\
do{\
    if (__builtin_constant_p(dir))\
    __inline_dma_cache_sync(addr, sz, dir);\
    else\
    __arc_dma_cache_sync(addr, sz, dir);\
}\
while(0);

int main(int argc, const char * argv[]) {
    
    
    
    
    return 0;
}

//编译器内部还有一些内建函数主要用来编译优化/性能优化/如__builtinconstantp(n)函数
//该函数主要用来判断参数n在编译时是否为常量,是常量的话函数返回1,否则函数返回0
//该函数常用于宏定义中用于编译优化,一个宏定义根据宏的参数是常量还是变量,可能实现的方法不一样,在内核中经常看到这样的宏
//很多计算或者操作在参数为常数时可能有更优化的实现,在这个宏定义中我们实现了两个版本,根据参数是否为常数,我们可以灵活选用不同的版本
