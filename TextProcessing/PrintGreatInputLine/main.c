//
//  main.c
//  PrintGreatInputLine
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXLINE 1000
#define LONGLINE 80

int getline(char line[], int maxline);

int main(int argc, const char * argv[]) {
    
    
    int len;
    char line[MAXLINE];
    
    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (len > LONGLINE)//如果输入行的长度大于80就输出,否则不进行任何操作,这一过程将一直循环到getline()返回一个等于0的输入行长度为止
        {
            printf("%s", line);
        }
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
    if (c == '\n')//读到换行符
    {
        s[j] = c;//将换行符写入倒数第二个位置
        ++j;
        ++i;
    }
    s[j] = '\0';//把字符'\0'(空字符,值为0)插入到创建的数组的末尾,以标记字符串的结束
    return i;//返回字符串长度
}

//打印长度大于80个字符的所有输入行
