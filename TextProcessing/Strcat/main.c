//
//  main.c
//  Strcat
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void strcat(char s[], char t[]);

int main(int argc, const char * argv[]) {
    
//    char *sp = "abc";
//    char *sn = "xdef";
//
//    strcat(sp, sn);
//    printf("%s\n", sp);
    
    
    return 0;
}

void strcat(char s[], char t[])
{
    int i, j;
    i = j = 0;
    while (s[i] != '\0')//判断是否结尾
        i++;
    while ((s[i++] = t[j++]) != '\0')//复制
        ;
}

//将字符串T连接到字符串S的尾部,S必须有足够大的空间
//标准库中的该函数返回指向新字符串的指针
