//
//  main.c
//  CharCount
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    
    long nc = 0;
    int c;//变量c方便调试
    while ((c=getchar()) != EOF)//无变量c的简化版本((getchar()) != EOF)
    {
        nc++;
    }
    printf("%ld\n", nc);
    
    
    
    return 0;
}

//字符统计,输入测试时要使用行首Ctrl+Z来作为结束符而不是回车
//换行符并不是输入结束,而是将键盘上敲下的字符送入输入缓冲区供函数使用
//Ctrl+Z表示一个字符,其ASCII码为26
//只有当Ctrl+Z单独位于一行的行首时才表示输入的终止EOF,即无论何时都推荐先回车,再Ctrl+Z,再回车结束输入
//当Ctrl+Z位于行中和行末时输入都不会结束,而是结束当前行的输入
//且第一个Ctrl+Z作为ASCII码为26字符并入前面输入,并且在第一个Ctrl+Z后输入的字符和回车将不存入当前行,但输入回车有换行效果
//Linux下用Ctrl+D
//输入11Ctrl+Z1Ctrl+Z回车Ctrl+Z测试输出3
//11Ctrl+Z(这三个字符有效,注意第一个Ctrl+Z)
