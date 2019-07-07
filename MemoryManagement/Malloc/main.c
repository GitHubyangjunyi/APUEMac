//
//  main.c
//  Malloc
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

//static int *pi = malloc(sizeof(int));//常量表达式中不允许函数调用

int main(int argc, const char * argv[]) {
    

    char *pc = (char *)malloc(6);
    for (int i = 0; i < 8; i++)
    {
        pc[i] = 0;
    }
    
    for (int i = 0; i < 8; i++)
    {
        printf("%d\n", pc[i]);
    }
    
    free(pc);//堆信息损坏,引起程序错误
    
    char GETCHAR = getchar();
    return 0;
}

//分配内存时,堆管理器维护的数据结构中会保存额外的信息,这些信息包括块大小和其他一些信息
//通常放在紧挨着分配块的位置,如果应用程序的写入操作超出了这块内存,数据结构可能会被破坏,造成堆损坏
//静态/全局指针
//初始化静态或全局变量时不能调用函数,因为全局变量是在函数和可执行代码外部声明的,赋值语句这类代码必须出现在函数内部
