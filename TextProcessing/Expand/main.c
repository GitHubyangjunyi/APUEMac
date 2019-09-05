//
//  main.c
//  Expand
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void expand(char s1[], char s2[]);

int main(int argc, const char * argv[]) {
    
    char s[] = "a-z";
    char ss[26] = " ";
    expand(s, ss);
    printf("%s", ss);
    printf("\n");
    
    
    return 0;
}

void expand(char s1[], char s2[])
{
    int i, j;
    char c;
    
    i = j = 0;
    while ((c = s1[i++]) != '\0')
        if (s1[i] == '-' && s1[i + 1] >= c)
        {
            i++;
            while (c < s1[i])
                s2[j++] = c++;
        }
        else
            s2[j++] = c;
    s2[j] = '\0';
}

//expand(s1,s2)将字符串s1中类似a-z一类的速记符号在字符串s2中扩展为完全等价的完整列表abc...xyz
//该函数可以处理大小写,并且可以处理a-b-c,a-z0-9与-a-z等类似的情况,作为前导和尾随的-字符原样输出
//
//expand函数先把s1中的一个字符读到变量c中,再检查下一个字符,如果下一个字符是-且再下一个字符大于或等于保存在变量c中的字符
//expand函数就会对这个速记符号进行扩展,否则expand函数就把变量c中的字符直接复制到s2中
//
//expand函数只能对ASCII字符进行处理,例如将把速记符号a-z扩展为与之等价的列表abc...xyz
//把!-~扩展为!"#...ABC...XYZ...abc...xyz...|}~
