//
//  main.c
//  ConditionalCompilation
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    
    
    
    return 0;
}

//条件编译
//条件包含:使用条件语句对预处理本身进行控制,这种条件语句的值是在预处理执行的过程中进行计算
//这种方式为在编译过程中根据计算所得的条件值选择性地包含不同代码提供了一种手段
//#if语句对其中的常量整型表达式(其中不能包含sizeof/类型转换运算符或enum常量)进行求值
//若该表达式的值不等于0,则包含其后的各行,直到遇到#endif #elif或#else语句为止(预处理器语句#elif类似于else if)
//在#if语句中可以使用表达式define(名字),该表达式的值遵循下列规则:当名字已经定义时,其值为1,否则其值为0
//例如为了保证hdr.h文件的内容只被包含一次,可以将该文件的内容包含在下列形式的条件语句中:
//
//    #if !define(HDR)
//    #define HDR
//        hdr.h文件的内容
//    #endif
//
//第一次包含头文件hdr.h时将定义名字HDR,此后再次包含该文件时,会发现该名字已经定义,这样将直接跳转到#endif处
//类似的方式也可以用来避免多次重复包含同一文件
//如果多个头文件能够一致地使用这种方式,那么每个头文件都可以将它所依赖的任何头文件包含进来,用户不必考虑和处理头文件之间的各种依赖关系
//
//下面的这段预处理器代码首先测试系统变量SYSTEM,然后根据该变量的值确定包含哪个版本的头文件:
//    #if SYSTEM == SYSV
//        #define HDR "sysv.h"
//    #elif SYSTEM == BSD
//        #define HDR "bsd.h"
//    #elif SYSTEM == MSDOS
//        #define HDR "msdos.h"
//    #else
//        #define HDR "default.h"
//    #endif
//    #include HDR
//
//C语言专门定义了两个预处理语句#ifdef与#ifndef
//用来测试某个名字是否已经定义,上面的第一个例子可以改写为下列形式:
//    #ifndef HDR
//    #define HDR
//        hdr.h文件的内容
//    #endif
