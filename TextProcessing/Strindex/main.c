//
//  main.c
//  Strindex
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);
int strindexx(char source[], char searchfor[]);
int strindexxfast(char source[], char searchfor[]);

char pattern[] = "ould";

int main(int argc, const char * argv[]) {
    
    char line[MAXLINE];
    int found = 0;
    
    while (getline(line,MAXLINE) > 0)
        if (strindex(line,pattern) >= 0)
        {
            printf("%s", line);
            found++;
        }
    return found;
}

int getline(char line[], int max)//将行保存到line中并返回该行的长度
{
    int c, i;
    i = 0;
    while (--max > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

int strindex(char source[], char searchfor[])//返回searchfor在source中的位置,未找到返回-1
{
    int i, j, k;
    
    for ( i = 0; source[i] != '\0'; i++)
    {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
            ;
        if (k > 0 && searchfor[k] == '\0')
            return i;
    }
    
    return -1;
}

int strindexx(char source[], char searchfor[])//返回字符串searchfor在字符串source中最右边出现的位置, 当s不包含t时返回 - 1
{
    int i, j, k, pos;
    
    pos = -1;
    for (i = 0; source[i] != '\0'; i++)
    {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
            ;
        if (k > 0 && searchfor[k] == '\0')
            pos = i;
    }
    
    return pos;
}

int strindexxfast(char source[], char searchfor[])//(高效率版)返回字符串searchfor在字符串source中最右边出现的位置, 当s不包含t时返回 - 1
{
    int i, j, k;
    
    for (i = strlen(source) - strlen(searchfor); i >= 0; i--)
    {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
            ;
        if (k > 0 && searchfor[k] == '\0')
            return i;
    }
    
    return -1;
}

//strindex(s,t)函数返回字符串t在字符串s中的出现的开始位置或索引,当s不包含t时返回-1
//strindexx(s,t)函数返回字符串t在字符串s中最右边出现的位置,当s不包含t时返回-1
//
//strindex函数与strindexx函数很相似,两者的区别是strindex函数只要找到字符串t在字符串中的第一次最左边出现的位置就结束了
//而strindexx函数在找到字符串t在字符串s中的匹配之后只记录其位置,然后继续搜索,因为它必须返回字符串t在s中最后一次最右边出现的位置
//
//strindexxfast从字符串s的尾部最右边再向串首推进字符t的长度个字符的位置开始寻找字符串t
//如果没有匹配,strindexxfast将从右向左后退一个位置并再次进行比较
//这样当strindexxfast函数在字符串s中找到字符串t时,将立刻返回变量i,此时i就是字符串t在字符串s中最右边出现的位置
