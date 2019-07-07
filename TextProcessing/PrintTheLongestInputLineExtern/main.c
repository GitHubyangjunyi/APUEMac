//
//  main.c
//  PrintTheLongestInputLineExtern
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXLINE 1000    //允许输入的最大行长度
//定义并声明了各个外部变量的类型,编译程序将为它们分配存储单元
int max;                //目前发现的最长行的长度
char line[MAXLINE];        //当前的输入行
char longest[MAXLINE];    //用于保存最长的行

int getline(void);//为了与老版本C兼容,ANSI C将空参数表看成老版本C的声明方式,并且对参数表不再检查
void copy(void);//在ANSI C,如果要声明空参数表,必须使用void显式声明

int main(int argc, const char * argv[]) {
    
    int len;
    extern int max;
    extern char longest[];
    
    max = 0;
    while((len = getline()) > 0)
        if (len > max)
        {
            max = len;
            copy();
        }
    if (max > 0)//存在这样的行
    {
        printf("%s", longest);
    }
    
    return 0;
}

int getline(void)//将一行读入到s中并返回长度,getline读到文件末尾时返回0,每行至少包括一个字符,只包含换行符的行长度为1(特别版)
{//没必要声明数组的长度,该数组的大小是在main函数中设置的
    int c, i;
    extern char line[];
    
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)//事先不知道输入行的长度,要进行界限检查
    {
        line[i] = c;
    }
    if (c == '\n')
    {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';//把字符'\0'(空字符,值为0)插入到创建的数组的末尾,以标记字符串的结束
    return i;
}

void copy(void)//将from复制到to,假定to足够大(特别版)
{
    int i = 0;
    extern char line[], longest[];
    while ((longest[i] = line[i]) != '\0')//字符'\0'也将被拷贝过去,由(to[i] = from[i])执行
    {
        ++i;
    }
}

//打印最长输入行(使用外部变量版,失去通用性)
//while(还有未处理的行)
//if(该行比已处理的最长行还要长)
//    保存该行
//    保存该行的长度
//打印最长行
//当把数组名用作参数时,传递给函数的值是数组起始元素的位置或地址,并不复制数组元素本身
//在被调函数中可以通过数组下标访问或修改数组元素的值
//
//函数中的每个局部变量只在函数被调用时存在,执行完毕退出时消失,称为自动变量的原因
//由于自动变量只在函数调用执行期间存在,所以在函数两次调用之间,不保留前次调用时的赋值
//且在每次进入函数时都要显式赋值,如果自动变量没有赋值,其中存放的是无效值
//
//static存储类,这种类型的局部变量在多次函数调用之间保持值不变
//
//除了自动变量外还可以定义位于所有函数外部的变量,所有的函数都可以通过变量名访问这种变量
//由于外部变量可以在全局范围内访问,函数间可以通过外部变量交换数据,而不必使用参数表
//外部变量在程序执行期间一直存在,即使在对外部变量赋值的函数返回后,这些变量依旧保持原来的值不变
//外部变量必须定义在所有函数外,且只能定义一次,定义后编译程序将为它分配存储单元
//在每个需要访问外部变量的函数中,必须声明相应的外部变量,此时说明其类型
//声明时使用extern显示声明,也可以通过上下文隐式声明
//函数在使用外部变量之前必须要知道,一种方式是在函数中使用extern类型的声明
//某些情况下可以省略extern声明,在源文件中,如果外部变量的定义出现在使用它的函数之前,那么在那个函数中就没有必要使用extern声明
//因此main,getline,copy中的几个extern声明都是多余的
//通常的做法是,所有外部变量的定义都放在源文件的开始处,这样就可以省略extern声明
//
//如果程序包含在多个源文件中,而某个变量在file1中定义,而在file2和file3中使用
//那么在file2和file3中就需要使用extern声明来建立该变量与其定义之间的联系
//通常把变量和函数的extern声明放在一个单独的文件中,一般称为头文件
//并在每个源文件的开头使用#include包含进来,并约定头文件后缀名.h
//标准库中的函数就是在类似于<stdio.h>的头文件中声明的
//
//定义表示创建变量或分配存储单元,而声明指的是说明变量的性质,但并不分配存储单元
//定义表示创建变量或分配存储单元,而声明指的是说明变量的性质,但并不分配存储单元
