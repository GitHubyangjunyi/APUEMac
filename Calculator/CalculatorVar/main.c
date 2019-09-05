//
//  main.c
//  CalculatorVar
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

int main(int argc, const char * argv[]) {
    
    int type, i, var = 0;
    double op2, v;//存放临时操作数
    char s[MAXOP];//中转存放栈中的内容
    double variable[26];
    
    for (i = 0; i < 26; i++) {
        variable[i] = 0.0;
    }
    
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
            case '=':
                pop();
                if (var >= 'A' && var <= 'Z') {
                    variable[var - 'A'] = pop();
                }
                else
                    printf("error: no variable name\n");
                break;
            case '\n':
                v = pop();
                printf("\t%.8g\n", v);//到达输入行末尾将栈顶的值弹出并打印
                break;
            default:
                if (type >= 'A' && type <= 'Z')
                    push(variable[type - 'A']);
                else if(type == 'v')
                    push(v);
                else
                    printf("error: unknown command %s\n", s);
                break;
        }
        var = type;
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

//给计算器程序增加处理变量的命令,提供26个具有单个英文字母变量名的变量
//增加一个变量存放最近打印的值
//用大写字母A-Z表示变量,这些字母作为数组变量的索引,小写字母v存放最近打印的值
//在遇到一个变量名A-Z或者v时,计算器将该变量压入栈中
//操作符=将堆栈中某个元素赋值给=前面的字母变量
//3 A = 将3赋值给变量A
//2 A + 将2和3相加同时将5赋值给v
