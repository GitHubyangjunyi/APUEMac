//
//  main.c
//  Getint
//
//  Created by 杨俊艺 on 2019/8/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

int getint(int *pb);
int getch(void);
void ungetchs(int c);

int main(int argc, const char * argv[])
{
    
    int n, arr[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    for (n = 0; n < 9 && getint(&arr[n]) != EOF; n++)
    {
        ;
    }
    for (n = 0; n < 9; n++)
    {
        printf("%d\n", arr[n]);
    }
    
    
    
    return 0;
}

int getint(int *pn)//getint接受自由格式的输入并执行转换,将输入的字符流分解成整数,且每次调用得到一个整数,getint返回转换后得到的整数,并在到达输入结尾时返回EOF
//将标识是否到达文件末尾的状态作为getint函数的返回值,同时使用一个指针参数存储转换后的整数并传回给主调函数,函数scanf实现就采用这种方式
{
    int c,sign;
    
    while (isspace(c = getch()))//跳过空白符
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetchs(c);//输入不是一个数字则将提前读入的字符送回缓冲区
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF)
        ungetchs(c);
    return c;//输入中包含一个有意义的数字时返回一个正值
}

#define BUFSIZE 100

char buf[BUFSIZ];    //用于ungetch函数的缓冲区
int bufp = 0;        //buf中下一个空闲位置
//程序中经常会出现不能确定它已经读入的输入是否足够,除非超前多读入一些输入,读入一些字符以合成一个数字的情况便是一例
//在看到第一个非数字字符之前,已经读入的数的完整性是不能确定的,由于程序要超前读入一个字符,导致有最后一个字符不属于当前所要读入的数
//所以需要反读不需要的字符,每当程序多读入一个字符时,就把它压回到输入中,对代码其余部分而言就好像没有读入该字符一样,可以编写一对互相协作的函数来模拟反取字符操作
//getch用于读入下一个待处理的字符,而ungetch则用于把字符放回到输入中,此后在调用getch函数时,在读入新输入之前先返回ungetch函数放回那个字符
//ungetch函数把要压回的字符放到一个共享的缓冲区中,当该缓冲区不为空时,getch函数就从缓冲区中读取字符,当缓冲区为空时,getch函数调用getchar直接从输入读取字符
//下表变量标记缓冲区中当前字符的位置
//由于缓冲区与下标变量是供getch和ungetch共享的,且在两次调用之间必须保持值不变,因此必须是外部变量
//标准库中提供了函数ungetc,将一个字符压回到栈中
int getch(void)//取一个字符(可能是压回的字符)
{
    return (bufp > 0) ? buf[--bufp] : getchar();//如果缓冲区没有字符再读,否则再次从输入中取数,如果缓冲区中有则从缓冲区读
}

void ungetchs(int c)//把字符压回到输入中
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
