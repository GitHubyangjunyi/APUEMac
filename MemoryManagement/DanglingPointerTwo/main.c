//
//  main.c
//  DanglingPointerTwo
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    
    //更难察觉的迷途指针:一个以上的指针引用同一块内存区域而其中一个指针被释放
    int *pOne = (int *)malloc(sizeof(int));
    *pOne = 5;
    
    int *pTwo = pOne;//两个指针引用同一个内存地址称为别名
    free(pOne);
    
    printf("free(pOne) pOne = %d\n", *pOne);
    
    *pTwo = 555;//迷途指针
    
    printf("free(pOne) pOne = %d\n", *pOne);//555
    printf("free(pOne) pTwo = %d\n", *pTwo);//555
    
    
    
    return 0;
}
