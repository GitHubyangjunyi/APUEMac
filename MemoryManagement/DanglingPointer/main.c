//
//  main.c
//  DanglingPointer
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    
    int *pDangling = (int *)malloc(sizeof(int));
    *pDangling = 100;    //pDangling变量持有整数的地址,但堆管理器可以重复利用这块内存,且其中可能存放非整型数据
    printf("*pDangling = %d\n", *pDangling);
    
    free(pDangling);//使用free函数后就不应该再使用这块内存了,但是大部分运行时系统不会阻止后续的访问和修改,但结果不可预期
    *pDangling = 111;
    printf("free(pDangling) *pDangling = %d\n", *pDangling);
    
    //free(pDangling);//重复释放触发运行时异常
    
    
    
    return 0;
}

//如果内存已经释放,但是指针还在引用原始内存,这样的指针称为迷途指针(悬空指针)
//迷途指针没有指向有效的对象,有时候也称为过早释放
//使用迷途指针的问题
//1.访问内存时行为未定义
//2.如果内存不可访问则是段错误
//3.潜在安全隐患
//导致的原因
//1.访问已经释放的内存
//2.返回的指针指向的是上次函数调用中的自动变量
