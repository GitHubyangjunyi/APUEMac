//
//  main.c
//  Atof
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

double atofs(char s[]);
double atofsx(char s[]);
int getline(char line[], int max);

int main(int argc, const char * argv[]) {
    
    double atof(char s[]);//需要显示声明返回值类型,把这一行注释掉下面的输出将是无意义的,此时使用的是标准库中的atof函数
    printf("%lf\n", atof("234.5"));
    
    printf("%lf\n", atofs("234.5"));
    
    printf("%lf\n", atofsx("234.5e+6"));
    
    
    ////简单计算器:在每行中读取一个数,并对它们求和////
    double sum, atofs(char[]);
    char line[MAXLINE];
    int getline(char line[], int max);
    
    sum = 0;
    while (getline(line, MAXLINE) > 0)
    {
        printf("\t%g\n", sum += atofs(line));
    }
    
    return 0;
}

double atofs(char s[])//将数字串s转换成相应的双精度浮点数
{
    double val, power;
    int i, sign;
    val = 0.0;//初始化否则报错
    
    for (i = 0; isspace(s[i]); i++)//跳过空白符
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val == 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 *  val + (s[i] - '0');
        power *= 10.0;
    }
    
    return sign * val / power;
}

double atofsx(char s[])//对atofs函数的扩充,可以处理形如123.45e+6的科学表示法
{
    double val, power;
    int i, exp, sign;
    val = 0.0;//初始化否则报错
    
    for (i = 0; isspace(s[i]); i++)//跳过空白符
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val == 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 *  val + (s[i] - '0');
        power *= 10.0;
    }
    val= sign * val / power;
    
    if (s[i] == 'e' || s[i] == 'E')//如果有指数部分则进行进一步计算
    {
        sign = (s[++i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exp = 0; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');
        if (sign == 1)
            while (exp-- > 0 )
                val *= 10;
        else
            while (exp-- > 0)
                val /= 10;
    }
    
    return val;//如果没有指数部分直接返回
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

//函数atofs的声明与定义必须一致,如果atofs函数与调用它的函数main放在同一源文件中,并且类型不一致,编译器就会检测到错误
//但是如果atofs函数是单独编译的,这种不匹配的错误就无法检测出来,atofs函数将返回double类型的值,而main函数却将返回值按int类型处理,最后的结果值是无意义的
//原因是如果没有函数原型,则函数将在第一次出现的表达式中被隐式地声明,比如
//    sum += atofs(line)
//如果先前没有声明过的一个名字出现在某个表达式中,并且其后紧跟一个左圆括号,那么上下文就会认为该名字是一个函数名字,该函数的返回值将被假定为int类型
//但上下文并不对其参数作任何假设,并且如果该函数声明不包含参数,例如
//    double atofs()
//那么编译程序也不会对函数atofs的参数作任何假设,并会关闭所有的参数检查
//对空参数表的这种特殊处理是为了使新的编译器能编译比较老的C语言程序,不过在新编写的程序中不提倡这样做
//如果函数带有参数,则要声明它们,如果没有则使用void进行声明
//
//
//atofs和atofsx(扩充版)的区别:
//前半部分完全相同,atofs跳过了多余的空白符,记录符号位,把字符串转换为相应的数值之后返回结果
//但是扩展版本还必须对可能遇到的科学表示法进行处理
//科学表示法中的可选指数部分由atofsx的后半部分处理,如果没有指数部分,返回保存在val中的数值
//如果有指数部分,指数部分的符号将被保存在变量sign中,而指数部分的值将被计算并保存在exp中
//
//注意,用10去除而不是用0.1去乘是因为0.1无法用二进制精确地表示出来
//在大多数机器上,0.1的二进制表示法都要比0.1小一些,用10.0乘上0.1并不能精确地得到1.0
