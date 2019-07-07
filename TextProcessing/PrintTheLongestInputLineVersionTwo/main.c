//
//  main.c
//  PrintTheLongestInputLineVersionTwo
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(int argc, const char * argv[]) {
    
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    
    max = 0;
    while ((len = getline(line, MAXLINE)) > 0)//1.读取一行并原样输出刚才的输入行,进入下一次行读取
    {
        printf("%d, %s", len, line);
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    //2.输入结束,如果有最大行,输出最大行
    if (max > 0)
    {
        printf("%s", longest);
    }
    
    
    return 0;
}

int getline(char s[], int lim)
{
    int c, i, j;
    
    j = 0;//用来记录被复制到字符串s中的字符个数
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim-2)//给换行符和字符串结束符留位置
        {
            s[j] = c;
            ++j;
        }
    
    if (c == '\n')//读到换行符
    {
        s[j] = c;//将换行符写入倒数第二个位置
        ++j;
        ++i;
    }
    s[j] = '\0';//把字符'\0'(空字符,值为0)插入到创建的数组的末尾,以标记字符串的结束
    return i;//返回字符串长度
}

void copy(char to[], char from[])
{
    int i = 0;
    
    while ((to[i] = from[i]) != '\0')
    {
        ++i;
    }
}

//PrintTheLongestInputLineVersionTwo 打印最长输入行版本二,可以打印任意长度的输入行的长度,并尽可能多地打印文本
