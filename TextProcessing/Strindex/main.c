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

int getlines(char line[], int max);
int strindex(char source[], char searchfor[]);
int strindexx(char source[], char searchfor[]);
int strindexxfast(char source[], char searchfor[]);

char pattern[] = "ould";//要匹配的模式字符串

int main(int argc, const char * argv[]) {
    
    char line[MAXLINE];
    int found = 0;//记录匹配的数目
    
    while (getlines(line,MAXLINE) > 0)//如果还有未处理的行
        if (strindex(line,pattern) >= 0)//如果匹配则打印出该行
        {
            printf("%s", line);
            found++;
        }
    return found;
}

int getlines(char line[], int max)//将行保存到line中并返回该行的长度
{
    int c, i;
    c = i = 0;
    while (--max > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

int strindex(char source[], char searchfor[])//strindex(s,t)函数返回字符串searchfor在字符串source中的出现的开始位置或索引,当s不包含t时返回-1
{                                            //如果后续需要更复杂的模式匹配,只需替换strindex即可
    int i, j, k;                             //标准库提供的函数strstr类似于该函数,但是库函数返回的是指针而不是下标值
    
    for ( i = 0; source[i] != '\0'; i++)//从源字符串头到尾
    {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)//未到达模式末尾且一个字符一个字符都匹配
            ;
        if (k > 0 && searchfor[k] == '\0')//如果k大于0且模式确实匹配到末尾结束
            return i;
    }
    
    return -1;//未匹配返回-1
}

int strindexx(char source[], char searchfor[])//返回字符串searchfor在字符串source中最右边出现的位置,当s不包含t时返回-1
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

int strindexxfast(char source[], char searchfor[])//(高效率版)返回字符串searchfor在字符串source中最右边出现的位置,当s不包含t时返回-1
{
    int i, j, k;
    
    for (i = strlen(source) - strlen(searchfor); i >= 0; i--)//从source尾部再向串首推进字符串searchfor的长度个字符的位置开始寻找字符串searchfor
    {                                                        //如果没有匹配将从右向左后退一个位置并再次进行比较,当在字符串source中找到字符串searchfor时立刻返回变量i,i此时的取值就是字符串searchfor在source中最右边出现的位置
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
            ;
        if (k > 0 && searchfor[k] == '\0')
            return i;
    }
    
    return -1;
}

//将输入中包含特定"模式"或字符串的各行打印出来(这是UNIX程序grep的特例)
//例如这个程序在下列一组文本行中查找包含字符串"ould"的行
//
//strindex函数与strindexx函数很相似,两者的区别是strindex函数只要找到字符串t在字符串中的第一次最左边出现的位置就结束了
//而strindexx函数在找到字符串t在字符串s中的匹配之后只记录其位置,然后继续搜索,因为它必须返回字符串t在s中最后一次最右边出现的位置
//
//strindexxfast从字符串s的尾部最右边再向串首推进字符t的长度个字符的位置开始寻找字符串t
//如果没有匹配,strindexxfast将从右向左后退一个位置并再次进行比较
//这样当strindexxfast函数在字符串s中找到字符串t时,将立刻返回变量i,此时i就是字符串t在字符串s中最右边出现的位置
//
//书上的输入:
//Ah Love! could you and I with Fate conspire
//To grasp this sorry Scheme of Things entire,
//Would not we shatter it to bits -- and then
//Re-mould it nearer to the Heart's Desire!
//书上的输出
//Ah Love! could you and I with Fate conspire
//Would not we shatter it to bits -- and then
//Re-mould it nearer to the Heart's Desire!
//实际输入输入输出:
//Ah Love! could you and I with Fate conspire
////Ah Love! could you and I with Fate conspire
////To grasp this sorry Scheme of Things entire,
//Would not we shatter it to bits -- and then
///Would not we shatter it to bits -- and then
//Re-mould it nearer to the Heart's Desire!
////Re-mould it nearer to the Heart's Desire!
