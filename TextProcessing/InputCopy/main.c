//
//  main.c
//  InputCopy
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void Version();

int main(int argc, const char * argv[]) {
    
    int c;
    
    while ((c = getchar()) != EOF)
    {
        putchar(c);//行首只输入Ctrl+Z可以退出
    }
    
    printf("另一个版本\n");
    Version();
    
    return 0;
}

void Version()
{
    int c = getchar();
    while (c != EOF)
    {
        putchar(c);
        c = getchar();//行首只输入Ctrl+Z可以退出
    }
}

//将输入复制到输出
//
//读一个字符
//while(该字符不是文件结束字符)
//    输出刚读入的字符
//    读下一个字符
//
//只有当Ctrl+Z单独位于一行的行首时才表示输入的终止EOF
