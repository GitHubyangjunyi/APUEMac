//
//  main.c
//  MacroDefinition
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define SQUARE(x) x*x
#define SQUARES(x) (x)*(x)

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )

#define MALLOC(n,type) ( (type *)malloc( (n) * sizeof(type) ) )
//有一些任务根本无法使用函数实现,宏的第二个参数是类型,无法作为函数参数进行传递
#define SWAP(t, x, y) { t _z;    \
                        _z = y;    \
                        y = x;    \
                        x = _z;}

int main(int argc, const char * argv[]) {
    
    printf("小型计算的宏替代\n");
    int a = 5;
    printf("%d\n", SQUARE(a+1));//输出11而不是36,a+1*a+1=11
    printf("%d\n", SQUARES(a + 1));//输出36
    
    printf("比较的宏替代\n");
    int x = 5, y = 8;
    float flag = MAX(x, y);
    printf("flag=%f\n", flag);
    
    printf("类型参数的宏替代\n");
    int *pi = MALLOC(25, int);
    //pi = ((int *)malloc((25) * sizeof(int)));//上面的语句被替换成这一句
    
    printf("带副作用的宏参数\n");
    flag = MAX(x++, y++);
    printf("flag=%f\n", flag);
    printf("x=%d\n,y=%d\n", x, y);
    
    int number = count_one_bits(11);
    printf("number = %d\n", number);
    
    int swapx = 10, swapy = 100;
    SWAP(int, swapx, swapy);
    printf("swapx = %d\n", swapx);
    printf("swapy = %d\n", swapy);
    
    int GETCHAR = getchar();
    return 0;
}

int count_one_bits(unsigned value)//这个函数返回参数值中值为1的位的个数
{
    int ones;
    for (ones = 0; value != 0; value = value >> 1)
    {
        if (value % 2 != 0)
        {
            ones = ones + 1;
        }
    }
    return ones;
}

//#define正式描述:
//#define name stuff
//每当有符号name出现在这条指令后面时,预处理器就会把它替换成stuff
//#define机制包括了一个规定,允许把参数替换到文本中,这种实现通常称为宏或定义宏,下面是声明方式:
//#define name(parameter-list) stuff
//其中,parameter-list参数列表是一个由逗号分隔的符号列表,它们可能出现在stuff中,参数列表的左括号必须与name紧邻,如果两者之间有任何空白
//参数列表就会被解释为stuff的一部分,当宏被调用时,名字后面是一个由逗号分隔的值的列表,每个值都与宏定义中的一个参数相对应
//整个列表用一对括号包围,当参数出现在程序中时,与每个参数对应的实际值都将被替换到stuff中
//
//宏经常用于执行简单的计算,比如上面定义的MAX,至于为什么不用函数来完成这个任务,由两个原因:
//1.用于调用和从函数返回的代码可能比实际执行这个小型计算工作的代码更大,所以使用宏可以减小规模与提高速度
//2.更为重要的是,函数是类型相关的,函数的参数必须声明为一种特定的类型,所以它只能在类型合适的表达式上使用,而宏是类型无关的
//和使用函数相比,使用宏的不利之处在于每次使用宏时,一份宏定义代码的拷贝都将插入到程序中,增加代码的长度
//有一些任务根本无法使用函数实现,宏的第二个参数是类型,无法作为函数参数进行传递
//
//带副作用的宏参数
//当宏参数在宏定义中出现的次数超过一次时,如果这个参数具有副作用,那么当你使用这个宏参数时就可能导致不可预料的结果
//副作用就是表达式求值时出现的永久性效果
//x+1()不具有副作用
//x++()具有副作用
//
//宏虽然有缺陷,但还是很有价值的,<stdio.h>中有一个很实用的例子,getchar与putchar函数在实际中经常被定义为宏,避免处理字符时调用函数所需的运行时开销
//<ctype.h>中定义的函数也常常是通过宏实现的
//可以通过#undef指令取消名字的宏定义,这样做可以保证后续的调用是函数调用,而不是宏调用:
//    #undef getchar
//    int getchar(void) {...}
//
//形式参数不能用带引号的字符串替换,但是如果再替换文本中,参数名以#最为前缀则结果将被扩展为由实际参数替换该参数的带引号的字符串
//例如可以将它与字符串连接运算结合起来编写一个调试宏:
//    #define dprint(expr) printf(#expr " = %g\n", expr)
//使用语句调用该宏时
//    dprint(x/y)
//将被扩展为
//    dprint("x/y" " = %g\n", x/y)
//字符串被连接起来,等效于
//    dprint("x/y = %g\n", x/y)
//在实际参数中,每个双引号"将被替换为\",反斜杠\将被替换为\\,因此替换后的字符串是合法的字符串常量
//
//预处理器运算符##为宏扩展提供了一种连接实际参数的手段,如果替换文本中的参数与##相邻,该参数将被实际参数替换,##与前后的空白符将被删除,并对替换后的结果重新扫描
//    #define paste(front, back) front ## back
//
//    paste(name, 1)将建立记号name1
