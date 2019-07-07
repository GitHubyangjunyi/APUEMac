//
//  main.c
//  Histogram
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXHIST 15    //直方图的最大长度
#define MAXWORD 11    //允许的单词最大长度
#define IN      1     //词里面
#define OUT     0     //词外面

int main(int argc, const char * argv[]) {
    
    
    int c;
    int i;              //控制循环的变量,非关键
    int nc;             //单个单词的长度
    int state;
    int len;            //每一个直方图的长度
    int maxvalue;       //相同长度单词出现次数最多的值
    int ovflow;         //长度大于或等于MAXWORD的单词的数量
    int wl[MAXWORD];    //按单词长度值1~10,统计输入中各长度的单词数,存放在wl数组中,没有长度为0的单词
    
    state = OUT;
    nc = 0;             //一个单词的字符的个数
    ovflow = 0;         //长度大于或等于MAXWORD的单词的数量
    for ( i = 0; i < MAXWORD; ++i)//1.置零存放单词长度的数组,数组下标即是对应单词长度,比如wl[2]用于存放长度为2的单词出现的次数
        wl[i] = 0;
    
    while ((c = getchar()) != EOF)//2.统计数组下标所对应长度的单词出现次数
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            if (nc > 0)//如果一个单词nc > 0且它的长度小于允许的单词最大长度,程序将对相应的单词长度计数器加1
                if (nc < MAXWORD)
                    ++wl[nc];//对应单词长度计数器加1
                else//如果单词长度超过了允许的单词最大长度,程序将对ovflow变量加1以记录长度大于或等于MAXWORD的单词的个数
                    ++ovflow;
            nc = 0;//单词的字符的个数清零
        }
        else if (state == OUT)
        {
            state = IN;
            nc = 1;//开始一个新单词
        }
        else
            ++nc;//在一个单词内则只加字符数也就是单词长度
    }
    
    maxvalue = 0;
    for (i = 1; i < MAXWORD; ++i)//3.在读入全部单词后,程序将找出数组wl中的最大值maxvalue作为基准
    {
        if (wl[i] > maxvalue)
            maxvalue = wl[i];
    }
    
    for (i = 1; i < MAXWORD; ++i)//4.开始输出水平直方图
    {
        printf("%5d - %5d : ", i, wl[i]);
        if (wl[i] > 0)
        {
            if ((len = wl[i] * MAXHIST / maxvalue) <= 0)
                len = 1;
        }
        else
        {
            len = 0;
        }
        while (len > 0)
        {
            putchar('*');
            --len;
        }
        putchar('\n');
    }
    if (ovflow > 0)//5.输出超长的单词的个数
    {
        printf("There are %d words >= %d\n", ovflow, MAXWORD);
    }
    
    
    
    return 0;
}

//单词长度直方图(水平):打印输入中相同长度单词的出现次数的直方图
//空格,换行或制表符表示单词的结束
//如果有一个单词(nc>0)且它的长度小于允许的单词最大长度(nc<MAXWORD),程序将相应的单词的长度加一(++wl[nc])
//如果单词的长度超过了允许的单词最大长度(nc>=MAXWORD),程序将对变量ovflow加一以记录长度大于或等于MAXWORD的单词的个数
//变量len是根据MAXHIST和maxvalue的值计算出来的wl[i]所对应的直方图长度
//如果wl[i]大于0,就至少要打印一个星号
