//
//  main.c
//  OneLineOneWordVersionTwo
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define IN 1
#define OUT 0

int main(int argc, const char * argv[]) {
    int c, state;//用来记录是否在某个单词内部
    
    state = OUT;//1.初始化为在单词外部
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')//2.如果遇到空白符
        {
            if (state == IN)//3.遇到空白符的前提下,如果在单词内部,则输出换行并切换成在单词外部
            {
                printf("\n");
                state = OUT;
            }
        }
        else//4.如果不是空白符,输出字符并切换成在单词内部
        {
            putchar(c);//感觉可以改成这个版本二,如果是state==IN,再state=IN并没有什么功能性影响
            state = IN;
        }
    }
    
    return 0;
}

//每行一个单词打印输入版本二
//有bug
