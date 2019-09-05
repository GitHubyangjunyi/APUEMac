//
//  main.c
//  Htoi
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define YES 1
#define NO 0

int htoi(char s[]);

int main(int argc, const char * argv[]) {
    
    printf("%d\n", htoi("1A"));
    printf("%d\n", htoi("0x1A"));
    printf("%d\n", htoi("0X1A"));
    
    return 0;
}

int htoi(char s[])
{
    int i;
    int n;
    int hexdigit = 0;
    int inhex;
    
    i = 0;
    if (s[i]== '0')
    {
        ++i;
        if (s[i] == 'x' || s[i] == 'X')
        {
            ++i;
        }
    }
    n = 0;
    inhex = YES;
    for (; inhex == YES; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' &&s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            inhex = NO;
        if (inhex == YES)//保证数组元素是一个合法的十六进制数字字符,其值在hexdigit的范围内
            n = 16 * n + hexdigit;
    }
    
    return n;
}

//把十六进制组成的字符串(包含可选的前缀0x或0X)转换为与之等价的整型值
//字符串中允许包含的数字包括:0~9 a~f A~F
