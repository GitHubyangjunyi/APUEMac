//
//  main.c
//  Itoa
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

void itoa(int n, char s[]);
void itoas(int n, char s[]);
void itoax(int n, char s[], int w);
void reverse(char s[]);

int main(int argc, const char * argv[]) {
    
    
    char s[] = "";
    
    itoa(15, s);
    printf("%s\n", s);
    
    itoa(-15, s);
    printf("%s\n", s);
    
    itoas(-15, s);
    printf("%s\n", s);
    
    itoax(15, s, 4);
    printf("%s\n", s);
    

    return 0;
}

void itoa(int n, char s[])//在数的对二的补码表示法中,itoa函数不能处理最大的负数,修改后的itoas函数在任何机器上运行时都能打印出正确的值
{
    int i, sign;
    
    if ((sign = n) < 0)//记录符号
        n = -n;       //使n成为正数
    i = 0;
    //以反序生成数字
    do//使用do...while是因为即使n为0也要放一个字符到s中
    {
        s[i++] = n % 10 + '0';//取得下一个数字
    } while ((n /= 10) > 0);//删除该数字
    if (sign < 0)//如果是负数
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itoas(int n, char s[])
{
    int i, sign;
    void reverse(char s[]);
    
    sign = n;//变量sign保存n的初值
    i = 0;
    do//使用do...while是因为即使n为0也要放一个字符到s中
    {
        s[i++] = abs(n % 10) + '0';//用宏abs计算n % 10 的绝对值,只需把取模操作的结果转换为正数,就能绕过无法把负数转换为一个正数的问题
    } while ((n /= 10) != 0);//修改之前的(n /= 10) > 0以避免因为n是负数而陷入无限循环
    if (sign < 0)//如果是负数
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void itoax(int n, char s[], int w)//第三个参数为最小字段宽度,保证转换后d所得的结果至少具有第三个参数指定最小宽度,并在必要时在所得结果的左边补足空格
{
    int i, sign;
    void reverse(char s[]);
    
    sign = n;//变量sign保存n的初值
    i = 0;
    do
    {
        s[i++] = abs(n % 10) + '0';//用宏abs计算n % 10 的绝对值,只需把取模操作的结果转换为正数,就能绕过无法把负数转换为一个正数的问题
    } while ((n /= 10) != 0);//修改之前的(n /= 10) > 0以避免因为n是负数而陷入无限循环
    if (sign < 0)//如果是负数
        s[i++] = '-';
    while (i < w)
        s[i++] = ' ';//在必要时给字符串补足空格
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])//字符串翻转
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

//itoa函数将数字n转换为字符串并保存到s中,itoax函数可以接收三个参数,第三个参数为最小字段宽度,在必要时应在所得结果的左边填充一定的空格
//
//在数的对二的补码表示法中,itoa函数不能处理最大的负数,修改后的itoas函数在任何机器上运行时都能打印出正确的值
//事实上是因为,最大的负数n = -(2的(字长-1)次方)无法通过语句    n = -n    转换为一个正数
//因为对二的补码所能表示的最大正数是(2的(字长-1)次方) - 1
//比如8位字长能表示-128~127
//先逆序求出各位数字,再用reverse函数对字符串s做一次颠倒以获得最终结果
//具体地说在itoas函数中,用变量sign保存n的初值,用宏abs计算n % 10 的绝对值,只需把取模操作的结果转换为正数,就能绕过无法把负数转换为一个正数的问题
