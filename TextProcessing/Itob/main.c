//
//  main.c
//  Itob
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(int argc, const char * argv[]) {
    
    char s[] = "";
    itob(15, s, 16);
    printf("%s\n", s);
    
    
    
    return 0;
}

void itob(int n, char s[], int b)
{
    int i, j, sign;
    void reverse(char s[]);
    
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        j = n % b;    //返回一个0到b-1之间的值
        s[i++] = (j <= 9) ? j + '0' : j + 'a' - 10;
    } while ((n /= b) > 0);//    n /= b调整n的值,只要(n /= b) > 0,该过程将一直持续下去
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
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
    while (j < i)
    {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        --i;
        ++j;
    }
}

//itob(n, s, b)将整数n转换为以b为底的数,并将转换结果以字符形式保存到字符串s中,b控制进制
//先按逆序生成b进制数的每一位数字,再用函数reverse对字符串s做一次颠倒得到最终结果
