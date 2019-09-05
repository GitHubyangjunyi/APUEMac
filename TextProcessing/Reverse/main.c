//
//  main.c
//  Reverse
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char s[]);
void reverses(char s[]);

int main(int argc, const char * argv[]) {
    
    char line[MAXLINE];//用来存放字符串
    
    while (getline(line, MAXLINE) > 0)
    {
        reverse(line);
        reverses(line);
        printf("%s", line);
    }
    
    return 0;
}

int getline(char s[], int lim)
{
    int c, i, j;
    
    j = 0;//用来记录被复制到字符串s中的字符个数
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim - 2)//给换行符和字符串结束符留位置
        {
            s[j] = c;
            ++j;
        }
    if (c == '\n')
    {
        s[j] = c;
        ++j;
        ++i;
    }
    s[j] = '\0';//字符串最后以'\0'结尾
    return i;//返回字符串长度
}

void reverse(char s[])
{
    int i, j;
    char temp;
    
    i = 0;
    
    while (s[i] != '\0')
    {
        ++i;
    }
    --i;//1.找到字符串s的末尾,然后从'\0'处倒退一个位置
    
    if (s[i] == '\n')//2.如果倒退后的位置是一个换行符,那么再倒退一个位置
    {
        --i;
    }
    
    j = 0;//3.开始交换文本
    while (j  < i)
    {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        --i;
        ++j;
    }
}

void reverses(char s[])
{
    int c, i, j;
    
    for (i = 0, j = strlen(s) - 1; i < j; i++ , j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

//将字符串S中的字符顺序颠倒过来,每次颠倒一个输入行中的字符顺序
