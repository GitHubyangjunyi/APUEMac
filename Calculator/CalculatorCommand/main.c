//
//  main.c
//  CalculatorCommand
//
//  Created by 杨俊艺 on 2019/8/11.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>//为了使用atof()函数
#include <ctype.h>

#define MAXOP 100    //操作数或运算符的最大长度
#define NUMBER '0'  //表示找到一个数

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetchs(int);
void clear(void);

int main(int argc, const char * argv[]) {
    
    int type;
    double op1, op2;//存放临时操作数
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
            case '?'://查询栈顶元素
                op2 = pop();
                printf("\t%.8g\n", op2);
                push(op2);
                break;
            case 'c'://清除堆栈元素
                clear();
                break;
            case 'd'://赋值栈顶元素
                op2 = pop();
                push(op2);
                push(op2);
                break;
            case 's'://交换栈顶元素
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
                break;
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

void clear(void)//清楚堆栈内容
{
    sp = 0;
}

int getop(char s[])
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')//跳过空格或者制表符
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')//不是数或不是小数点则返回操作符
        return c;
    i = 0;
    if (isdigit(c))//收集整数部分
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')//收集小数部分
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
