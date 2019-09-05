//
//  main.c
//  Trim
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

unsigned long trim(char s[]);

int main(int argc, const char * argv[]) {
    
    char s[] = "abcd \t \n";
    trim(s);
    printf("%s", s);
    
    
    
    return 0;
}

unsigned long trim(char s[])
{
    unsigned long n;
    //strlen函数返回字符串的长度,循环从字符串末尾开始反方向扫描寻找第一个不是空格符,制表符以及换行符的字符
    for (n = (unsigned long)strlen(s) - 1; n >= 0; n--)//当找到符合条件的第一个字符,或当循环控制变量n变成负数时(即整个字符串扫描完成),循环终止
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n + 1] = '\0';//即使字符串仅包含空白符或为空,函数也是正确的
    return n;
}

//删除字符串尾部的空格符,制表符和换行符
