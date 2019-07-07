//
//  main.c
//  Strpbrk
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    
    
    
    
    
    return 0;
}

void strpbrk(char s1[], char s2[])
{
    int i, j;
    for (i = 0; s1[i] != '\0'; i++)
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;
    return -1;
}

//将字符串S2中的任一字符在字符串S1中第一次出现的位置作为结果返回,如果S1中不包含S2中的字符,返回-1
//标准库函数strpbrk具有相同的功能,但它返回的是指向该位置的指针
