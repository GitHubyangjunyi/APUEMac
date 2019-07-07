//
//  main.c
//  Free
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void compute(int size);

int main(int argc, const char * argv[]) {
    

    int *pi = (int *)malloc(sizeof(int));
    *pi = 1234567890;
    printf("%d\n", *pi);
    
    free(pi);//内存已经释放,但可能包含原值,这种情况称为迷途指针
    
    printf("%d\n", *pi);
    
    
    //未定义行,free函数传入的参数不是由malloc类的函数所分配的
    int num = 987654321;
    int *pnum = &num;
    printf("%d\n", num);
    printf("%d\n", *pnum);
    
    //free(*pnum);//运行时异常
    //printf("%d\n", num);
    //printf("%d\n", *pnum);
    
    //未定义行为二,将已经释放的指针赋值为NULL
    //已经释放的指针还是有可能引起问题,如果试图解引用一个已经释放的指针,行为将是未定义的
    //所以有时候会显式将指针赋值为NULL以表示该指针无效
    //后续再使用该指针会造成运行时异常,为了解决迷途指针问题,但是除了初始化情况下,都不能将NULL赋值给指针
    int *pNull = (int *)malloc(sizeof(int));
    free(pNull);
    pNull = NULL;
    
    //重复释放问题
    int *pRefree = (int *)malloc(sizeof(int));
    free(pRefree);
    //free(pRefree);//重复释放触发运行时异常
    
    //重复释放问题(不明显问题)
    int *pRefreeOne = (int *)malloc(sizeof(int));
    int *pRefreeTwo = pRefreeOne;//两个指针引用同一个内存地址称为别名
    free(pRefreeOne);
    //free(pRefreeTwo);//重复释放触发运行时异常
    //堆管理器很难判断一个块是否已经被释放,因此不会试图去检测是否两次释放了同一块内存
    //这通常会导致堆损坏和程序终止,即使程序没有终止,意味着程序逻辑可能存在问题,因为同一块内存没理由释放两次
    //有人建议free函数应该在返回时将NULL或其他某个特殊值赋给自身的参数,但指针是传值的,因此free函数无法显式地给它赋值为NULL
    //堆一般利用操作系统的功能来管理内存,堆的大小可能在程序创建后就固定不变了,也可能可以增长
    //不过堆管理器不一定会在调用free函数时将内存返还给操作系统,释放的内存只是可供应用程序的后续使用
    //所以如果程序先分配内存后释放,从操作系统角度看,释放的内存通常不会反应在应用程序的内存使用上
    
    return 0;
}

//free函数用来将不再使用的内存返回系统,函数原型
//    void free(void *ptr);
//指针参数应该指向由malloc类函数分配的内存的地址,这块内存会被返回给系统
//尽管指针还指向这块内存区域,但应该将它看成指向垃圾数据
//如果传递给free函数的参数是NULL指针,通常它什么都不做,如果传入的指针所指向的内存不是由malloc类的函数所分配的,那么行为未定义
