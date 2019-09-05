//
//  main.c
//  HistogramVersionTwo
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
    int i;               //控制循环的变量,非关键
    int j;
    int nc;              //单个单词的长度
    int state;
    int maxvalue;        //相同长度单词出现次数最多的值
    int ovflow;          //长度大于或等于MAXWORD的单词的数量
    int wl[MAXWORD];
    
    state = OUT;
    nc = 0;            //一个单词的字符的个数
    ovflow = 0;        //长度大于或等于MAXWORD的单词的数量
    for (i = 0; i < MAXWORD; ++i)//1.置零存放单词长度的数组,数组下标即是对应单词长度,比如wl[2]用于存放长度为2的单词出现的次数
    {
        wl[i] = 0;
    }
    
    while ((c = getchar()) != EOF)//2.统计数组下标所对应长度的单词出现次数
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            if (nc > 0)
                if (nc < MAXWORD)//如果一个单词nc > 0且它的长度小于允许的单词最大长度,程序将对相应的单词长度计数器加1
                    ++wl[nc];//对应单词长度计数器加1
                else
                    ++ovflow;//如果单词长度超过了允许的单词最大长度,程序将对ovflow变量加1以记录长度大于或等于MAXWORD的单词的个数
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
    //#define MAXHIST 15        //直方图的最大长度
    for (i = MAXHIST; i > 0; --i)//4.开始输出垂直直方图,i从最高高度15递减到1,可以理解为能够到达的高度(能够达到15,能够达到14,能够达到13,以此类推)
    {
        for ( j = 1; j < MAXWORD; ++j)//j从1递增到10
            if (wl[j] * MAXHIST / maxvalue >= i)//能够>=i表示次数能够达到与最大值当前所在频度的位置
                printf("   * ");
            else
                printf("     ");
        putchar('\n');
    }
    
    for (i = 1; i < MAXWORD; ++i)//5.输出1~10
        printf("%4d ", i);
    putchar('\n');
    
    for (i = 1; i < MAXWORD; ++i)//6.输出数组下标所对应单词长度的单词的出现次数
        printf("%4d ", wl[i]);
    putchar('\n');
    
    if (ovflow > 0)//7.输出超长的单词的个数
        printf("There are %d words >= %d\n", ovflow, MAXWORD);
    
    
    return 0;
}

//单词长度直方图(垂直):打印输入中单词长度的直方图
//从开始直到求值maxvalue的过程与前一个程序完全相同
//然后这个程序需要计算数组wl中的每一个元素并判断是否需要在数组元素对应位置上打印一个星号
//这一判断过程必不可少,因为垂直方向的直方图的所有直方条是同步打印的
//最后两个for循环用来输出数组wl各个元素下标和取值
