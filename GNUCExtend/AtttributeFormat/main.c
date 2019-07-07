//
//  main.c
//  AtttributeFormat
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

//从这里开始看
//GNU C通过attribute扩展的format属性用来指定变参函数的参数格式检查
//使用方法如下,格式说明:
//    __attribute__((format(archetype, string-index, first-to-check)))
//    void LOG(const char *fmt, ...)    __attribute__((format(printf, 1, 2)));
//因为我们实现的是变参函数,参数的个数和格式都不确定,那编译器编译程序时如何检查我们参数的格式是否正确呢?
//其实很简单,通过给LOG函数添加attribute((format(printf, 1, 2)))这个属性声明就是告诉编译器:你知道printf函数不?
//你怎么对这个函数参数格式检查的就按同样的方法对LOG函数进行检查
//属性format(printf, 1, 2)有三个参数,第一个参数printf是告诉编译器,按照printf函数的检查标准来检查
//第2个参数表示在LOG函数所有的参数列表中,格式字符串的位置索引,第3个参数是告诉编译器要检查的参数的起始位
//变参函数其参数个数跟printf函数一样是不固定的,那么编译器如何检查我们的打印格式是否正确呢?
//我们只需要将格式字符串的位置告诉编译器就可以了,比如在第2行代码中
//    LOG("I am litao\n");
//    LOG("I am litao, I have %d houses!\n", 0);
//    LOG("I am litao, I have %d houses! %d cars\n", 0, 0);
//在这个LOG函数中有2个参数,第一个是格式字符串,第2个是要打印的一个常量值0,用来匹配格式字符串中的格式符
//什么是格式字符串呢?顾名思义如果一个字符串中含有格式符,那这个字符串就是格式字符串,比如这个格式字符串:"I am litao, I have %d houses!\n"里面含有格式符%
//我们也可以叫它占位符,打印的时候后面变参的值会代替这个占位符,在屏幕上显示出来
//我们通过format(printf, 1, 2)属性声明告诉编译器LOG函数的参数,格式字符串的位置在所有参数列表中的索引是1,即第一个参数
//要编译器帮忙检查的参数在所有的参数列表里索引是2,知道了LOG参数列表中格式字符串的位置和要检查的参数位置,编译器就会按照检查printf的格式打印一样
//对LOG函数进行参数检查,如果我们的LOG函数定义为下面形式
//void LOG(int num, char *fmt, ...)  __attribute__((format(printf, 2, 3)));
//在这个函数定义中多了一个参数num,格式字符串在参数列表中的位置发生了变化,在所有的参数列表中索引为2
//要检查的第一个变参的位置也发生了变化,索引为3,那我们使用format属性声明时就要写成format(printf,2,3)的形式了
//变参函数的设计与实现
//对于一个普通函数,我们在函数实现中不用关心实参,只需要在函数体内对形参直接引用即可,当函数调用时,传递的实参和形参个数和格式是匹配的
//在函数体内因为预先不知道传进来的参数类型和个数,所以实现起来会稍微麻烦一点,首先要解析传进来的实参,保存起来,然后才能接着像普通函数一样对实参进行处理
//我们接下来就定义一个变参函数,实现的功能很简单即打印传进来的实参值
void print_num(int count, ...)
{
    int *args = &count + 1;
    for (int i = 0; i < count; i++)
    {
        printf("*args: %d\n", *args);
        args++;
    }
}
//变参函数的参数存储其实跟main函数的参数存储很像,由一个连续的参数列表组成,列表里存放的是每个参数的地址
//在上面的函数中有一个固定的参数count,这个固定参数的存储地址后面,就是一系列参数的指针,在print_num函数中先获取count参数地址
//然后使用&count + 1就可以获取下一个参数的指针地址,使用指针变量args保存这个地址,并依次访问下一个地址就可以打印传进来的各个实参值了
//变参函数改进版
//上面的程序使用一个int *的指针变量依次去访问实参列表,改进程序使用char *类型的指针来实现这个功能,使之兼容更多的参数类型
void print_num2(int count, ...)
{
    char *args = (char *)&count + 4;
    for (int i = 0; i < count; i++)
    {
        printf("*args: %d\n", *(int *)args);
        args += 4;//这一语句在Linux VS Code中报错?
    }
}
//在这个程序中我们使用char *类型的指针,涉及到指针运算一定要注意每一个参数的地址都是4字节大小,所以我们获取下一个参数的地址是(char *)&count + 4;
//不同类型的指针加1操作转换为实际的数值运算是不一样的,对于一个指向int类型的指针变量p,p + 1表示p + 1 * sizeof(int)
//对于一个指向char类型的指针变量p,p + 1表示p + 1 * sizeof(char),两种不同类型的指针,其运算细节就体现在这里,当然程序后的运行结果跟上面的程序是一样的
//对于变参函数编译器或计算机系统一般会提供一些宏给程序员用来解析函数的参数,这样程序员就不用自己解析参数了,编译器提供的宏有:
//    va_list:                typedef char* va_list
//    va_start(args, fmt):    根据fmt的地址获取fmt后面参数的地址并保存到args指针变量
//    va_end(args):            释放args指针并将其赋值为NULL
void print_num3(int count, ...)//V3.0版本
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        printf("*args: %d\n", *(int *)args);
        args += 4;//这一语句在Linux VS Code中报错?
    }
    va_end(args);
}
//在V3.0版本中我们使用编译器提供的三个宏省去了解析参数的麻烦,但打印的时候我们还必须自己实现
//在V4.0版本中我们继续改进,使用vprintf函数实现我们的打印功能,vprintf函数的声明在stdio.h头文件
//CRTIMP int __cdecl __MINGW_NOTHROW    \
//    vprintf (const char*, __VALIST);
//vprintf函数有2个参数,一个是格式字符串指针,一个是变参列表,在下面的程序里我们将使用va_start解析后的变参列表
//直接传递给vprintf函数实现打印功能
void my_printf(char *fmt, ...)//V4.0版本
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
//上面的my_printf()函数基本上实现了跟printf()函数相同的功能,支持变参和多种格式的数据打印,接下来我们还需要对其添加format属性声明
//让编译器在编译时像检查printf一样检查my_printf()函数的参数格式
//void __attribute__((format(printf,1,2))) my_printfaf(char *fmt,...)//V5.0版这个函数在Linux下可用
//{
//    va_list args;
//    va_start(args,fmt);
//    vprintf(fmt,args);
//    va_end(args);
//}
//
//接下来实现自己的日志打印函数
//如果你坚持看到了这里可能会问有现成的打印函数可用为什么还要费这么大的劲去实现自己的打印函数?
//原因其实很简单,自己实现的打印函数除了可以实现自己需要的打印格式,还有2个优点,即可以实现打印开关控制/优先级控制
//闭上迷茫的双眼好好想象一下你在调试一个模块或者一个系统,有好多个文件,如果你在每个文件里添加printf打印,调试完成后再删掉是不是很麻烦?
//我们自己实现的打印函数,通过一个宏开关就可以直接关掉或打开,比较方便,比如下面的代码
#define DEBUG //打印开关
//void __attribute__((format(printf, 1, 2))) my_printfaflog(char *fmt, ...)//Linux下可用
//{
//    #ifdef DEBUG
//    va_list args;
//    va_start(args, fmt);
//    vprintf(fmt, args);
//    va_end(args);
//    #endif
//}
//当我们定义一个DEBUG宏时,my_printfaflog函数实现普通的打印功能,当这个DEBUG宏没有定义,LOG函数就是个空函数,通过这个宏我们就实现了打印函数的开关功能
//除此之外你可以通过宏设置一些打印等级,比如可以分为ERROR/WARNNING/INFO/LOG等级,根据你设置的打印等级,模块打印的log信息也会不一样
//在Linux内核的各个模块中你会经常看到大量的自定义打印函数或宏,如pr_debug/pr_info等


int main(int argc, const char * argv[]) {
    
    ////可变参数函数////
    printf("print_num:\n");
    print_num(5, 1, 2, 3, 4, 5);
    
    printf("print_num2:\n");
    print_num2(5, 1, 2, 3, 4, 5);
    
    printf("print_num3:\n");
    print_num3(5, 1, 2, 3, 4, 5);
    ////vprintf////
    int num = 100;
    my_printf("I am litao, I have %d car\n", num);//I am litao, I have 0 car
    
    
    
    return 0;
}
