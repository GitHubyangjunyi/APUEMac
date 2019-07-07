//
//  main.c
//  AtttributeWeak
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

//GNU C通过attribute声明weak属性可以将一个强符号转换为弱符号
//使用方法如下
//    void __attribute__((weak)) func(void);
//    int num __attribute__((weak));
//编译器在编译源程序时,无论你是变量名还是函数名,在它眼里都是一个符号而已,用来表征一个地址
//编译器会将这些符号集中存放到一个叫符号表的section中
//在一个软件工程项目中可能有多个源文件,由不同工程师开发,有时候可能会遇到这种情况:
//A工程师在他负责的A.c源文件中定义了一个全局变量num
//B工程师在他负责的B.c源文件中定义了一个同名全局变量num
//那么当我们在程序中打印变量num的值时是该打印哪个值呢?
//这时候就需要用编译链接的原理知识来分析这个问题了,编译链接的基本过程其实很简单,主要分为三个阶段:
//    编译阶段:编译器以源文件为单位将每一个源文件编译为一个.o后缀的目标文件,每一个目标文件由代码段/数据段/符号表等组成
//    链接阶段:链接器将各个目标文件组装成一个大目标文件,链接器将各个目标文件中的代码段组装在一起,组成一个大的代码段
//             各个数据段组装在一起,组成一个大的数据段,各个符号表也会集中在一起组成一个大的符号表
//             最后再将合并后的代码段/数据段/符号表等组合成一个大的目标文件
//    重定位:     因为各个目标文件重新组装,各个目标文件中的变量和函数的地址都发生了变化,所以要重新修正这些函数和变量的地址
//             这个过程称为重定位,重定位结束后就生成了可以在机器上运行的可执行程序
//上面举例的工程项目在编译过程中的链接阶段可能就会出现问题:A.c和B.c文件中都定义了一个同名变量num,那链接器到底该用哪一个呢?
//这个时候就需要引入强符号和弱符号的概念了
//在一个程序中无论是变量名还是函数名,在编译器的眼里就是一个符号而已,符号可以分为强符号和弱符号
//    强符号:函数名/初始化的全局变量名
//    弱符号:未初始化的全局变量名
//在一个工程项目中对于相同的全局变量名和函数名,我们一般可以归结为下面三种场景
//    强符号 + 强符号
//    强符号 + 弱符号
//    弱符号 + 弱符号
//强符号和弱符号在解决程序编译链接过程中出现的多个同名变量或函数的冲突问题非常有用,一般我们遵循下面三个规则
//    一山不容二虎
//    强弱可以共处
//    体积大者胜出
//这是我编的顺口溜,主要意思就是在一个项目中不能同时存在两个强符号,比如你在一个多文件的工程中定义两个同名的函数或初始化的全局变量
//那么链接器在链接时就会报重定义的错误,但一个工程中允许强符号和弱符号同时存在
//比如你可以同时定义一个初始化的全局变量和一个未初始化的全局变量,这种写法在编译时是可以编译通过的
//编译器对这种同名符号冲突在作符号决议时一般会选用强符号,丢掉弱符号
//还有一种情况就是,一个工程中同名的符号都是弱符号,那编译器该选择哪个呢?谁的体积大,即谁在内存中存储空间大就选谁
//我们接下来写一个简单的程序来验证上面的理论,定义两个源文件:main.c和func.c
////main.c
//
//    int a;
//    int b = 2;
//
//    void func(void);
//
//    int main(void)
//    {
//        printf("main：a = %d\n", a);
//        printf("main: b = %d\n", b);
//        func();
//        return 0;
//    }
//
////func.c
//
//    int a = 1;
//    int b;
//
//    void func(void)
//    {
//        printf("func：a = %d\n", a);
//        printf("func: b = %d\n", b);
//    }
//
//编译并运行
//    main : a = 1
//    main : b = 2
//    func : a = 1
//    func : b = 2
//我们在main.c和func.c中分别定义了两个同名全局变量a和b,但是一个是强符号,一个是弱符号,链接器在链接过程中,看到冲突的同名符号会选择强符号
//所以你会看到无论是main函数还是func函数,打印的都是强符号的值
//一般来讲不建议在一个工程中定义多个不同类型的弱符号,编译的时候可能会出现各种各样的问题
//在一个工程中也不能同时定义两个同名的强符号,即初始化的全局变量或函数,否则就会报重定义错误
//但是我们可以使用GNU C扩展的weak属性将一个强符号转换为弱符号
//
////func.c
//
//    int a __attribute__((weak)) = 1;
//    void func(void)
//    {
//    printf("func：a = %d\n", a);
//    }
//
////main.c
//
//    int a = 4;
//    void func(void);
//    int main(void)
//    {
//        printf("main：a = %d\n", a);
//        func();
//        return 0;
//    }
//
//编译并运行
//    main: a = 4
//    func: a = 4
//
//我们通过weak属性声明将func.c中的全局变量a转换为一个弱符号,然后在main.c里同样定义一个全局变量a并初始化为4
//链接器在链接时会选择main.c中的这个强符号,所以在两个文件中,打印变量a的值都是4
//
//接下来讨论函数的强符号和弱符号
//链接器对于同名变量冲突的处理遵循上面的强弱规则,对于函数同名冲突同样也遵循相同的规则,函数名本身就是一个强符号,在一个工程中定义两个同名的函数
//编译时肯定会报重定义错误,但我们可以通过weak属性声明将其中一个函数转换为弱符号
////func.c
//    int a __attribute__((weak)) = 1;
//    void __attribute__((weak)) func(void)
//    {
//        printf("func：a = %d\n", a);
//    }
//
////main.c
//    int a = 4;
//    void func(void)
//    {
//        printf("I am a strong symbol!\n");
//    }
//    int main(void)
//    {
//        printf("main：a = %d\n", a);
//        func();
//        return 0;
//    }
//
//编译并运行
//main：a = 4
//I am a strong symbol!
//
//我们在main.c中重新定义了一个同名的func函数,然后将func.c文件中的func()函数通过weak属性声明转换为一个弱符号
//链接器在链接时会选择main.c中的强符号,所以我们在main函数中调用func()时,实际上调用的是main.c文件里的func()函数
//
//弱符号的用途是什么?
//在一个源文件中引用一个变量或函数,当我们只声明而没有定义时,一般编译是可以通过的,这是因为编译是以文件为单位的
//编译器会将一个个源文件首先编译为.o目标文件,编译器只要能看到函数或变量的声明,会认为这个变量或函数的定义可能会在其它的文件中,所以不会报错
//甚至如果你没有包含头文件,连个声明也没有,编译器也不会报错,顶多就是给你一个警告信息,但链接阶段是要报错的
//链接器在各个目标文件和库中都找不到这个变量或函数的定义,一般就会报未定义错误
//当函数被声明为一个弱符号时会有一个奇特的地方:当链接器找不到这个函数的定义时也不会报错
//编译器会将这个函数名,即弱符号,设置为0或一个特殊的值,只有当程序运行时调用到这个函数,跳转到0地址或一个特殊的地址才会报错
////func.c
//int a __attribute__((weak)) = 1;
//
////main.c
//    int a = 4;
//    void __attribute__((weak)) func(void);
//    int main(void)
//    {
//        printf("main：a = %d\n", a);
//        func();
//        return 0;
//    }
//
//编译并运行
//    main: a = 4
//    Segmentation fault(core dumped)段错误
//
//在这个示例程序中我们没有定义func()函数,仅仅是在main.c里作了一个声明,并将其声明为一个弱符号,编译这个工程你会发现是可以编译通过的
//只是到了程序运行时才会出错,为了防止函数运行出错我们可以在运行这个函数之前,先做一个判断,即看这个函数名的地址是不是0然后再决定是否调用并运行
//这样就可以避免段错误了,示例代码如下
////func.c
//    int a __attribute__((weak)) = 1;
//
////main.c
//    int a = 4;
//    void __attribute__((weak)) func(void);
//    int main(void)
//    {
//        printf("main：a = %d\n", a);
//        if (func)
//            func();
//        return 0;
//    }
//
//编译并运行
//    main: a = 4
//函数名的本质就是一个地址,在调用func之前,我们先判断其是否为0,为0的话就不调用了,直接跳过
//你会发现通过这样的设计,即使这个func()函数没有定义我们整个工程也能正常的编译链接和运行
//弱符号的这个特性在库函数中应用很广泛,比如你在开发一个库,基础的功能已经实现,有些高级的功能还没实现,那你可以将这些函数通过weak属性声明
//转换为一个弱符号,通过这样设置,即使函数还没有定义,我们在应用程序中只要做一个非0的判断就可以了,并不影响我们程序的运行
//等以后你发布新的库版本实现了这些高级功能,应用程序也不需要任何修改,直接运行就可以调用这些高级功能
//弱符号还有一个好处,如果我们对库函数的实现不满意,我们可以自定义与库函数同名的函数,实现更好的功能
//比如我们C标准库中定义的gets()函数,就存在漏洞,常常成为黑客堆栈溢出攻击的靶子
//int main(void)
//{
//    char a[10];
//    gets(a);
//    puts(a);
//    return 0;
//}
//C标准定义的库函数gets()主要用于输入字符串,它的一个Bug就是使用回车符来判断用户输入结束标志
//这样的设计很容易造成堆栈溢出,比如上面的程序,我们定义一个长度为10的字符数组用来存储用户输入的字符串,当输入一个长度大于10的字符串时就会发生内存错误
//接着我们定义一个跟gets()相同类型的同名函数,并在main函数中直接调用,代码如下
//    #include<stdio.h>
//
//    char * gets(char * str)
//    {
//        printf("hello world!\n");
//        return (char *)0;
//    }
//
//    int main(void)
//    {
//        char a[10];
//        gets(a);
//        return 0;
//    }
//
//编译并运行
//hello world!
//通过运行结果我们可以看到,虽然我们定义了跟C标准库函数同名的gets()函数,但编译是可以通过的
//程序运行时调用gets()函数时就会跳转到我们自定义的gets()函数中运行

char * gets(char * str)
{
    printf("hello world!\n");
    return (char *)0;
}

int main(int argc, const char * argv[]) {
    
    char a[10];
    gets(a);
    
    puts(a);
    
    
    
    return 0;
}
