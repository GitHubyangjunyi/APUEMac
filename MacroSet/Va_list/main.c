//
//  main.c
//  Va_list
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

int AveInt(int, ...);

int main(int argc, const char * argv[]) {
    
    printf("%d\t", AveInt(2, 2, 3));
    printf("%d\t\n", AveInt(4, 2, 4, 6, 8));
    
    int ten = 10;
    printf("%d minus %d is %d\n", ten);//printf()函数就是使用可变长参数,结果不可预料
    
    
    
    return 0;
}

int AveInt(int v, ...)
{
    int ReturnValue = 0;
    int i = v;
    va_list ap;
    va_start(ap, v);
    
    while (i > 0)
    {
        ReturnValue += va_arg(ap, int);
        i--;
    }
    
    va_end(ap);
    
    return ReturnValue /= v;
}

//可以先看Va_listCPlusPlus那个项目
//VA_LIST是在C语言中解决变参问题的一组宏,变参问题是指参数的个数不定,可以是传入一个参数也可以是多个
//可变参数中的每个参数的类型可以不同,也可以相同,可变参数的每个参数并没有实际的名称与之相对应,使用灵活
//
//typedef char *va_list;
//
//va_start宏,获取可变参数列表的第一个参数的地址,list是类型为va_list的指针,param1是可变参数最左边的参数
//#define va_start(list,param1)   ( list = (va_list)&param1+ sizeof(param1) )
//
//va_arg宏,获取可变参数的当前参数,返回指定类型并将指针指向下一参数,mode参数描述了当前参数的类型
//#define va_arg(list,mode)   ( (mode *) ( list += sizeof(mode) ) )[-1]
//
//va_end宏,清空va_list可变参数列表:
//#define va_end(list) ( list = (va_list)0 )
//
//注意:    以上sizeof()只是为了说明工作原理,实际实现中,增加的字节数需保证为int的整数倍
//比如:    #define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
//
//使用方法:
//1.首先在函数里定义一具VA_LIST型的变量,这个变量是指向参数的指针
//2.然后用VA_START宏初始化变量刚定义的VA_LIST变量
//3.然后用VA_ARG返回可变的参数,VA_ARG的第二个参数是你要返回的参数的类型,如果函数有多个可变参数的,依次调用VA_ARG获取各个参数
//4.最后用VA_END宏结束可变参数的获取
//
//可变参数是由宏实现的,但是由于硬件平台的不同,编译器的不同,宏的定义也不相同,下面是VC6.0中x86平台的定义
//    typedef char *va_list;     //TC中定义为void*
//    #define _INTSIZEOF(n)    ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) ) //为了满足需要内存对齐的系统
//    #define va_start(ap,v)    ( ap = (va_list)&v + _INTSIZEOF(v) )            //ap指向第一个变参的位置,即将第一个变参的地址赋予ap
//    #define va_arg(ap,t)       ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )   //获取变参的具体内容,t为变参的类型,如有多个参数,则通过移动ap的指针来获得变参的地址,从而获得内容
//    #define va_end(ap) ( ap = (va_list)0 )   //清空va_list,即结束变参的获取
//
//va_list ap;        //定义一个va_list变量ap
//va_start(ap, v);    //执行ap = (va_list)&v + _INTSIZEOF(v),ap指向参数v之后的那个参数的地址,即ap指向第一个可变参数在堆栈的地址
//va_arg(ap, t);    //((t)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))取出当前ap指针所指的值,并使ap指向下一个参数,ap＋ = sizeof(t类型)
//                    让ap指向下一个参数的地址,然后返回ap - sizeof(t类型)的t类型指针,这正是第一个可变参数在堆栈里的地址,然后用取得这个地址的内容
//va_end(ap);        //清空va_list ap
//
//使用VA_LIST应该注意的问题:
//1.因为va_start/va_arg/va_end等定义成宏,所以它显得很愚蠢,可变参数的类型和个数完全在该函数中由程序代码控制,它并不能智能地识别不同参数的个数和类型
//也就是说你想实现智能识别可变参数的话是要通过在自己的程序里作判断来实现的
//2.另外有一个问题,因为编译器对可变参数的函数的原型检查不够严格,对编程查错不利,不利于我们写出高质量的代码
//3.由于参数的地址用于VA_START宏,所以参数不能声明为寄存器变量或作为函数或数组类型
