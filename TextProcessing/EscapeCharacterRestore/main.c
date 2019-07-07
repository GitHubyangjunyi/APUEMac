//
//  main.c
//  EscapeCharacterRestore
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int c;
    
    while ((c = getchar()) != EOF)
    {
        if (c=='\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c=='\\')
            printf("\\\\");
        else
            putchar(c);
    }
    
    
    return 0;
}

//转义字符还原,将制表符还原成\t,退格符还原成\b,反斜杠还原成\\
//ANSI C语言中的所有转义字符序列
//\a    响铃
//\b    回退
//\f    换页
//\n    换行
//\r    回车
//\t    横向制表
//\v    纵向制表
//\\    反斜杠
//\?    问号
//\'    单引号
//\"    双引号
//\ooo    八进制数
//\xhh    十六进制数
//
//字符常量'\0'表示值为0的字符,也就是空字符null,通常用'\0'的形式代替0,以强调某些表达式的字符属性,但其数字值为0
