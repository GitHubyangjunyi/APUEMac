//
//  main.c
//  Calloc
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int *pi = calloc(5, sizeof(int));
    int *px = malloc(5 * sizeof(int));
    memset(px, 0, 5 * sizeof(int));//memset函数第一个参数是指向要填充的缓冲区的指针,第二个参数是填充缓冲区的值,最后一个参数是要填充的字节数

    
    return 0;
}

//calloc函数会在分配的同时清空内存    void *calloc(size_t numElements, size_t elementSize);
//calloc函数会根据两个参数的乘积来分配内存,并返回一个指向内存的第一个字节的指针
//如果不能分配内存则返回NULL,此函数最初用来辅助分配数组内存
//如果其中一个参数为0,calloc可能返回空指针,如果calloc无法分配内存就会返回空指针,而且全局变量errno会设置为ENOMEM(内存不足)
//这是POSIX错误码,有的系统上可能没有,早期的C使用cfree来释放calloc分配的内存
