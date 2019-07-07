//
//  main.c
//  Escape
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
void unescapes(char s[], char t[]);

int main(int argc, const char * argv[]) {
    
    
    
    
    
    return 0;
}

void escape(char s[], char t[])
{
    int i, j;
    
    for(i = j = 0; t[i] != '\0'; i++)
        switch (t[i])
    {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;
    
    for (i = j = 0; t[i] != '\0'; i++)
        if (t[i] != '\\')
            s[j++] = t[i];
        else
            switch (t[++i])
        {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            default:
                s[j++] = '\\';
                s[j++] = t[i];
                break;
        }
    s[j] = '\0';
}

void unescapes(char s[], char t[])//使用switch嵌套
{
    int i, j;
    
    for (i = j = 0; t[i] != '\0'; i++)
        switch (t[i])
    {
        case '\\':
            switch (t[++i])
        {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            default:
                s[j++] = '\\';
                s[j++] = t[i];
                break;
        }
            break;
        default:
            s[j++] = t[i];
            break;
    }
    s[j] = '\0';
}

//将字符串t复制到字符串s中,并在复制过程中将换行符,制表符等不可见字符分别转换成\t\n等相应的可见的转义字符序列,再写一个相反功能的函数
