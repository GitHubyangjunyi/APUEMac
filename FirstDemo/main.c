//
//  main.c
//  FirstDemo
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLS 20        //能够处理的最大列号
#define MAX_INPUT 1000    //每个输入行的最大长度
//#define将名字MAX_COLS定义为20,当这个名字以后出现在源文件中的任何地方时,会被替换为定义的值
//由于被定义为字面值常量,所以这些名字不能出现在有些普通变量可以出现的场合,比如赋值符的左边

//下面的声明称为函数原型,用于告诉编译器这些以后将在源文件中定义的函数的特征
//这样当函数调用时,编译器就能对他们进行准确性检查,函数原型中,参数的名字并非必须
//假如这个程序的源代码由几个源文件组成,那么使用该函数的源文件都必须写明该函数的原型
//把原型放在头文件中并用#include指令包含它们可以避免由于同一个声明的多份拷贝而引起的维护性问题
int read_column_numbers(int columns[], int max);
void rearrange(char *output, char const *input, int n_clumns, int const columns[]);
//第二和第四个参数被声明为const,表示函数将不会修改函数调用者所传递的这两个参数,无返回值的函数一般称为过程

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
 ** 这个程序从标准输入中读取输入并在标准输出中打印这些输入行
 ** 每个输入行的后面一行是该行内容的一部分
 ** 输入的第一行是一串列标号,串的最后以一个负数结尾
 ** 这些标号成对出现,说明需要打印的输入行的列范围
 ** 例如, 0 3 10 12 -1 表示第0列到第3列,第10列到第12列的内容将被打印
 */

int main(int argc, const char * argv[]) {
    
    int n_columns;                //进行处理的列标号
    int columns[MAX_COLS];        //需要处理的列数
    char input[MAX_INPUT];         //容纳输入行的数组
    char output[MAX_INPUT];        //容纳输出行的数组
    
    //读取该串列标号
    n_columns = read_column_numbers(columns, MAX_COLS);//MAX_COLS 20
    
    //读取处理和打印剩余的输入行
    while (gets(input) != NULL)
    {
        printf("Original input : %s\n", input);
        rearrange(output, input, n_columns, columns);
        printf("Rearranged line: %s\n", output);
    }
    
    return EXIT_SUCCESS;//EXIT_SUCCESS定义在stdlib.h中
}

//读取列标号,如果超出规定范围则不予理会
int read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;                //为什么ch被声明为整型,而事实上用来读取字符,因为EOF是个整型值,它的位数比字符类型多
    //把ch声明为整型是为了防止从输入读取的字符意外地被解释为EOF
    //取得列标号,如果所读取的数小于0则停止
    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0)
        num += 1;
    
    //确认已经读取的标号为偶数个,因为它们是成对出现的
    if (num % 2 != 0)
    {
        puts("Last column number is not paired.");
        exit(EXIT_FAILURE);//EXIT_FAILURE定义在stdlib.h中
    }
    
    //丢弃该行中包含最后一个数字的那部分内容
    while ((ch = getchar()) != EOF && ch != '\n')
        ;
    
    return num;
}

//处理输入行,将指定列的字符连接在一起,输出行以NUL结尾
void rearrange(char *output, char const *input, int n_columns, int const columns[])//const限定传入的参数不会被修改
{//前两个参数被声明为指针,但在实际函数调用时,传给它们的参数却是数组名,当数组名作为实参时,传给函数的实际上是一个指向数组起始地址的指针
    int col;        //columns数组的下标
    int output_col;    //输出列计数器
    int len;        //输入行的长度
    
    len = strlen(input);//获得字符串的长度
    output_col = 0;
    
    //处理每对标号
    for (col = 0; col < n_columns; col += 2)
    {
        int nchars = columns[col + 1] - columns[col] + 1;
        
        //如果输入行结束或输出行数组已满,就结束任务
        if (columns[col] >= len || output_col == MAX_INPUT - 1)
            break;
        
        //如果输出行数据空间不够,只复制可以容纳的数据
        if (output_col + nchars > MAX_INPUT - 1)
            nchars = MAX_INPUT - output_col - 1;
        
        //复制相关数据
        strncpy(output + output_col, input + columns[col], nchars);
        output_col += nchars;
    }
    
    output[output_col] = '\0';
}
//4 9 12 20 -1
//abcdefghijklmnopqrstuvwxyz
//Original input : abcdefghijklmnopqrstuvwxyz
//Rearranged line: efghijmnopqrstu
//Hello there, how are you?
//Original input : Hello there, how are you?
//Rearranged line: o ther how are
//I am fine, thanks.
//Original input : I am fine, thanks.
//Rearranged line:  fine,hanks.
//See you!
//Original input : See you!
//Rearranged line: you!
//Bye
//Original input : Bye
//Rearranged line:
