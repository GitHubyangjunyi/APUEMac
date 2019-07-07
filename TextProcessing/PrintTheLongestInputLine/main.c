//
//  main.c
//  PrintTheLongestInputLine
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXLINE 1000        //允许输入的最大行长度

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(int argc, const char * argv[]) {
    
    int len;                //目前行长度
    int max;                //目前发现的最长行的长度
    char line[MAXLINE];        //当前的输入行
    char longest[MAXLINE];    //用于保存最长的行
    
    max = 0;
    while((len = getline(line, MAXLINE)) > 0)
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    if (max > 0)//存在这样的行
        printf("%s", longest);
    
    
    return 0;
}

int getline(char s[], int lim)//将一行读入到s中并返回长度,getline读到文件末尾时返回0,每行至少包括一个字符,只包含换行符的行长度为1
{//没必要声明数组的长度,该数组的大小是在main函数中设置的
    int c, i;
    
    for ( i = 0; i < lim-1 && (c=getchar())!=EOF && c != '\n'; ++i)//事先不知道输入行的长度,要进行界限检查
    {
        s[i] = c;
    }
    if (c=='\n')//读到换行符
    {
        s[i] = c;//将换行符写入倒数第二个位置
        ++i;
    }
    s[i] = '\0';//把字符'\0'(空字符,值为0)插入到创建的数组的末尾,以标记字符串的结束
    return i;
}

void copy(char to[], char from[])//将from复制到to,假定to足够大,无需检查溢出
{
    int i = 0;
    
    while ((to[i] = from[i]) != '\0')//字符'\0'也将被拷贝过去,由(to[i] = from[i])执行
    {
        ++i;
    }
}

//打印最长输入行
//while(还有未处理的行)
//if(该行比已处理的最长行还要长)
//    保存该行
//    保存该行的长度
//打印最长行
//当把数组名用作参数时,传递给函数的值是数组起始元素的位置或地址,并不复制数组元素本身
//在被调函数中可以通过数组下标访问或修改数组元素的值
