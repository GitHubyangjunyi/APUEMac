//
//  main.c
//  CalculatorMath
//
//  Created by 杨俊艺 on 2019/8/11.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>//为了使用atof()函数
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100    //操作数或运算符的最大长度
#define NUMBER '0'  //表示找到一个数
#define NAME 'n'    //表示找到一个名字

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetchs(int);
void mathfnc(char s[]);

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
            case NAME:
                mathfnc(s);
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

int getop(char s[])//改进后的getop能够识别出一个由小写字母组成的字符串并把它返回为类型NAME,主程序将返回的NAME识别为一个合法的类型并调用函数mathfnc,getop并不知道具体该调用哪个数学函数,只负责识别并返回它找到的字符串,这样容易在mathfnc添加其他函数
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')//跳过空格或者制表符
        ;
    s[1] = '\0';
    i = 0;
    if (islower(c)) {
        while (islower(s[++i] = c = getch()))
            ;
            s[i] = '\0';
            if (c != EOF) {
                ungetchs(c);
            }
            if (strlen(s) > 1)
                return NAME;
            else
                return c;
    }
    if (!isdigit(c) && c != '.')//不是数或不是小数点则返回操作符
        return c;
    
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

void mathfnc(char s[])//可扩展
{
    double op2;
    
    if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(s, "cos") == 0)
        push(cos(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0){
        op2 = pop();
        push(pow(pop(), op2));
    }
    else
        printf("error: %s not supported\n", s);
}

//3.14159265 2 / sin
//1
//3.151592 2 / sin 0 cos +
//1.9999875
//3.141592 2 / sin 0 cos +
//2
//5 2 pow 4 2 pow +
//41
//25 + 16 = 41
