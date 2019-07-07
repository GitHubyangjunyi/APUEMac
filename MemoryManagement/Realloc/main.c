//
//  main.c
//  Realloc
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    char *stringOne;
    char *stringTwo;
    stringOne = (char *)malloc(16);
    strcpy(stringOne, "0123456789ab");//13字节,含null结束符
    
    stringTwo = realloc(stringOne, 8);
    printf("stringOne Value: %p [%s]\n", stringOne, stringOne);
    printf("stringTwo Value: %p [%s]\n", stringTwo, stringTwo);
    
    char *stringThree;
    char *stringFour;
    stringThree = (char *)malloc(16);
    strcpy(stringThree, "0123456789ab");//13字节,含null结束符
    
    stringFour = realloc(stringThree, 64);
    printf("stringOne Value: %p [%s]\n", stringThree, stringThree);
    printf("stringTwo Value: %p [%s]\n", stringFour, stringFour);
    
    
    
    return 0;
}

//realloc函数用来在之前分配的内存块的基础上,将内存重新分配为更大或更小的部分
//函数原型
//void *realloc(void *ptr, size_t size);
//
//第一个参数是指向原内存块的指针,第二个参数是请求的大小,重新分配的块大小和第一个参数引用的块大小不同,返回值是指向重新分配的内存的指针
//请求的大小可以比当前分配的字节大或者小,如果比当前分配的小,那么多余的内存会还给堆,不保证多余的内存被清空
//如果比当前分配的大,那么可能的话就在紧挨着当前分配内存的区域分配新内存,否则就在堆的其他区域分配并把旧的内存复制到新区域
//如果大小是0而指针非空,那么就释放内存,如果无法分配空间,则原来的内存块不变,但返回空指针且errno设置为ENOMEM
