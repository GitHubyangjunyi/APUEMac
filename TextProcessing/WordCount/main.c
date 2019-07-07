//
//  main.c
//  WordCount
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define IN 1
#define OUT 0

int main(int argc, const char * argv[]) {
    
    int c;        //存放下一个读入字符
    int nl;       //行数
    int nw;       //单词数
    int nc;       //字符数
    int state;    //状态标记
    
    state = OUT;//初始状态在单词外
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
        nc++;//1.读入不是EOF,字符数加1
        if (c == '\n')//2.一旦碰到换行符,行数加1
        {
            ++nl;
        }
        if (c == ' ' || c == '\n' || c == '\t')//3.一旦碰到空白符,切换状态为OUT
        {
            state = OUT;
        }
        else//4.不是空白符,判断状态,如果当前处于单词外,切换状态为IN,单词数加1
        {
            if (state == OUT)
            {
                state = IN;
                ++nw;
            }
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    
    return 0;
}

//单词数行数字符数统计,程序执行时,每当遇到单词的第一个字符,它就作为一个新的单词加以统计,state变量记录程序当前是否位于一个单词中,初值是不在一个单词中
