//
//  main.c
//  Squeeze
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void squeeze(char s[], int c);
void squeezes(char s1[], char s2[]);


int main(int argc, const char * argv[]) {
    
    
    
    
    return 0;
}

void squeeze(char s[], int c)//从字符串S中删除字符C
{
    int i;
    int j;
    
    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)    //每当出现一个不是C的字符时,把它复制到数组下标为j的位置,随后将j增加1,准备处理下一个字符
            s[j++] = s[i];
    s[j] = '\0';
    
}

void squeezes(char s1[], char s2[])//将s1中任何与字符串s2中字符匹配的字符都删除
{
    int i, j, k;
    
    for ( i = k = 0; s1[i] != '\0'; i++)
    {
        for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
            ;
        if (s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}

//从字符串S中删除字符C
//将s1中任何与字符串s2中字符匹配的字符都删除
