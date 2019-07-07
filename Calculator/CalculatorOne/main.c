//
//  main.c
//  CalculatorOne
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>//为了使用atof()函数
#include <ctype.h>

#define MAXOP 100    //操作数或运算符的最大长度
#define NUMBER '0'    //表示找到一个数

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);


int main(int argc, const char * argv[]) {
    
    int type;
    double op2;
    char s[MAXOP];
    
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();//减法不满足交换律,将第一个值弹出到临时变量中
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();//除法不满足交换律,将第一个值弹出到临时变量中
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    
    return 0;
}

#define MAXVAL 100    //栈val的最大深度

int sp = 0;            //下一个空闲栈位置
double val[MAXVAL];    //值栈
//如果变量定义在任何函数的外部,则称为外部变量,所以把push和pop必须共享的栈和栈顶指针定义在这两个函数外部,但是main函数本身并没有引用栈或栈顶指针,因此对main而言要隐藏它们
void push(double f)//把f压入到值栈中
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)//弹出并返回栈顶的值
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[])//获取下一个运算符或数值操作数,需要跳过空格与制表符,如果下一个字符不是数字或小数点,则返回,否则把这些数字字符串收集起来,并返回NUMBER,以标识数已经收集起来了
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')//不是数
        return c;
    i = 0;
    if (isdigit(c))//收集整数部分
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')//收集小数部分
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
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
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)//把字符压回到输入中
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

//目标是编写一个具有加减乘除四则运算的计算器程序,为了容易实现,使用逆波兰表示法替代普通的中缀表示法
//逆波兰表示法用在Forth和Postscript等语言和某些袖珍计算器上
//在逆波兰表示法中,所有的运算符都跟在操作数的后面,比如下列中缀表达式
//    (1 - 2) * (4 + 5)
//采用逆波兰表示法为
// 1 2 - 4 5 + *
//逆波兰表示法不需要园括号,只要知道每个运算符需要几个操作数就不会引起歧义
//计算器程序实现很简单,每个操作数都被依次压入栈中,当一个运算符到达时,从栈中弹出相应数目的操作数(对二元运算符来说是两个操作数)
//把该运算符作用于弹出的操作数,再把运算结果压入到栈中,对于上面的逆波兰表达式来说,首先把1和2压入到栈中,再用两者之差取代它们
//然后再将4和5压入栈中,再用两者之和9取代它们,最后从栈中取出-1和9,再把积-9压入栈顶,当到达输入行的末尾时,把栈顶值弹出并打印
//
//while(下一个运算符或操作数不是文件结束指示符)
//    if(是数字)
//        将该数压入到栈中
//    else if(是运算符)
//            弹出所需数目的操作数
//        执行运算
//            将结果压入到栈中
//    else if(是换行符)
//        弹出并打印栈顶的值
//    else
//        出错
//
//
//栈的压入弹出比较简单,但是如果把错误检测和恢复操作都加进来程序就会显得很长了
//最好把它们设计成独立的函数,另外还需要一个单独的函数来取得下一个输入的运算符或操作数
//
//另一个问题是把栈放在哪个位置,也就是说哪些例程可以直接访问它?
//一种可能是把它放在主函数中,把栈及其当前位置作为参数传递给对它执行压入或弹出操作的函数,但是main函数不需要了解控制栈的变量信息,而只进行压入弹出操作
//因此可以把栈及相关信息放在外部变量中,并只供push和pop访问,而main不能访问
//
//程序形式如下:
//#include ...
//#define ...
//
//main使用的函数声明
//main() {...}
//
//push与pop使用的外部变量
//void push(double f) {...}
//double pop(void) {...}
//
//int getop(char s[]) {...}
//
//被getop调用的函数
//
//关于该程序更多信息以及如何分割到若干个源文件中的情况参见小项目BlockStructure
//
