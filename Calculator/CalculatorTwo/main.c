//
//  main.c
//  CalculatorTwo
//
//  Created by 杨俊艺 on 2019/8/11.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>//为了使用atof()函数
#include <ctype.h>
#include <math.h>//为了使用atof()函数

#define MAXOP 100    //操作数或运算符的最大长度
#define NUMBER '0'  //表示找到一个数

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetchs(int);

int main(int argc, const char * argv[]) {
    
    int type;
    double op2;//存放临时操作数
    char s[MAXOP];//中转存放栈中的内容
    
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));//将数值压入栈中再读栈中下一个内容
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();//减法不满足交换律,将第一个值弹出到临时变量中
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();//除法不满足交换律,将第一个值弹出到临时变量中
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':/*改动的部分*/
                op2 = pop();
                if (op2 != 0.0) {
                    push(fmod(pop(), op2));//库函数fmod能计算出堆栈顶两个元素的除法余数
                }
                else
                    printf("error: zero divisor\n");
            case '\n':
                printf("\t%.8g\n", pop());//到达输入行末尾将栈顶的值弹出并打印
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

int getop(char s[])
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')//跳过空格或者制表符
        ;
    s[1] = '\0';
    i = 0;
    if (!isdigit(c) && c != '.' && c != '-')//不是数或不是小数点则返回操作符,改动的部分是该函数需要检查紧跟在符号-后面的那个字符以判断该符号到底代表一个减号还是一个负号
        return c;
    if (c == '-')//如果c是一个-字符
    {
        if (isdigit(c = getch()) || c == '.')//并且下一个字符是数字或者小数点则将这个下一个字符记录下来
            s[++i] = c;
        else//如果在c是一个-字符的前提下,下一个字符不是数字也不是小数点
        {
            if (c != EOF)//如果这个下一个字符已经是行尾了就反读行尾并返回减号
            {
                ungetchs(c);
                return '-';
            }
        }
    }
    //如果是符号则收集剩余数值
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)//如果c未到达末尾则反读一个字符
        ungetchs(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZ];    //用于ungetch函数的缓冲区
int bufp = 0;        //buf中下一个空闲位置

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

//1 -1 +
//0
//-10 3 %
//-1
//即正确
