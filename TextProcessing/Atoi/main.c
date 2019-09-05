//
//  main.c
//  Atoi
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);//标准库也有atoi函数,这里使用自定义的atoi函数
int atois(char s[]);

int main(int argc, const char * argv[]) {
    
    char s[4] = "12x4";//碰到x终止
    int ints = atoi(s);
    printf("%d\n", ints);
    
    char ss[4] = "1234";
    int intss = atoi(ss);
    printf("%d", intss);
    
    
    return 0;
}

int atoi(char s[])
{
    int i, n;
    n = 0;
    for ( i = 0; s[i] >= '0' && s[i] <= '9'; ++i)//一旦碰到非数值字母就终止循环
    {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

int atois(char s[])//这一版本更加通用,可以处理可选的前导空白符以及一个可选的加号或减号,标准库提供一个更完善的strtol,将字符串转换成长整型P50
{
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++)//跳过空白符
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')//跳过符号
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

//将数字串S转换成相应的整型数
//先读到1
//n = 10 * n + (s[i] - '0')
//n=1
//再读到2,此时1要变成10去加2
//n = 10 * n + (s[i] - '0')
//      10 * 1 + 2 =>12
//依次类推
