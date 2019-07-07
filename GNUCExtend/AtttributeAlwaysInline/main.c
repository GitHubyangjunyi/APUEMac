//
//  main.c
//  AtttributeAlwaysInline
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

static inline __attribute__((always_inline))//在Linux环境下去掉此行注释
int func(int a)
{
    return a + 1;
}

static inline void print_num(int a)
{
    printf("%d\n", a);
}

int main(int argc, const char * argv[]) {
    
    int i;
    i = func(3);
    print_num(10);
    
    
    return 0;
}

//noinline和always_inline这两个属性的用途是告诉编译器对我们指定的函数内联展开或不展开,它们的使用方法如下
//    static inline __attribute__((noinline)) int func();
//    static inline __attribute__((always_inline)) int func();
//内联函数使用inline声明即可,有时候还会用static和extern修饰,使用inline声明一个内联函数和使用关键字register声明一个变量一样
//只是建议编译器在编译时内联展开,使用关键字register修饰变量时只是建议编译器在给变量分配存储空间时将这个变量放到寄存器里
//这样程序的运行效率会更高,那编译器会不会放呢?编译器就要根据寄存器资源紧不紧张,这个变量用得频不频繁来做权衡
//同样当一个函数使用inline关键字修饰,编译器在编译时未必会内联展开,编译器也会根据实际情况
//比如函数体大小/函数体内是否有循环结构/是否有指针/是否有递归/函数调用是否频繁来做决定,比如GCC编译器一般是不会对内联函数展开的
//只有当编译优化选项开到-O2以上才会考虑是否内联展开,当我们使用noinline和always_inline对一个内联函数作了属性声明后
//编译器的编译行为就变得确定了,使用noinline声明就是告诉编译器不要展开,使用always_inline属性声明就是告诉编译器要内联展开
//什么是内联展开呢?我们不得不说一下内联函数的基础知识
//说起内联函数又不得不说函数调用开销,一个函数在执行过程中如果需要调用其它函数,一般会执行下面这个过程
//    保存当前函数现场
//    跳到调用函数执行
//    恢复当前函数现场
//    继续执行当前函数
//比如一个ARM程序在一个函数f1()中,我们对一些数据进行处理,运算结果暂时保存在R0寄存器中,接着要调用另外一个函数f2()
//调用结束后接着返回到f1()函数中继续处理数据,如果我们在f2()函数中使用到R0这个寄存器用于保存函数的返回值
//此时就会改变R0寄存器中的值,那么就篡改了f1()函数中的暂存运算结果,当我们返回到f1()函数中继续进行运算时结果肯定不正确,那怎么办呢?
//很简单,在跳到f2()执行之前先把R0寄存器的值保存到堆栈中,f()函数执行结束后再将堆栈中的值恢复到R0寄存器中,这样f1()函数就可以接着继续执行了
//就跟什么事情都没发生过一样,这种方法证明是OK的,现代计算机系统无论是什么架构和指令集,都是采用这种方法,虽然麻烦了点,无非就是多花点代价
//需要不断地保存现场/恢复现场,这就是函数调用带来的开销
//内联函数的好处
//对于一般的函数调用这种方法是没有问题的,但对于一些极端情况,比如说一个函数很小只有一行代码,而且被大量频繁的调用,如果每次调用都不断地保存现场
//执行时却发现函数只有一行代码,又要恢复现场,往往造成函数开销比较大,我们就可以将这个函数声明为内联函数,编译器在编译过程中遇到内联函数时,像宏一样
//将内联函数直接在调用处展开,这样做的好处就是减少了函数调用开销,直接执行内联函数展开的代码,不用再保存现场/恢复现场
//看到这里可能就有人纳闷了,内联函数既然跟宏的功能差不多,那为什么不直接定义一个宏而去定义一个内联函数呢?
//相对于宏,内联函数有以下几个优势
//    参数类型检查:内联函数虽然具有宏的展开特性,但其本质仍是函数,编译过程中编译器仍可以对其进行参数检查,而宏就不具备这个功能
//    便于调试    :函数支持的调试功能有断点/单步等等,内联函数也同样可以
//    返回值        :内联函数有返回值,返回一个结果给调用者,这个优势是相对于ANSI C说的,不过现在宏也可以有返回值和类型了,比如使用语句表达式定义的宏
//    接口封装    :有些内联函数可以用来封装一个接口,而宏不具备这个特性
//前面也讲过我们虽然可以通过inline关键字将一个函数声明为内联函数,但编译器不一定会对这个内联函数展开处理,编译器也要进行评估,权衡展开和不展开的利弊
//内联函数并不是完美无瑕也有一些缺点,比如说会增大程序的体积,如果在一个文件中多次调用内联函数,多次展开,那整个程序的体积就会变大
//在一定程度上会造成CPU的取址效率降低,程序执行效率降低,函数的作用之一就是提高代码的复用性,我们将常用的一些代码或代码块封装成函数,进行模块化编程
//而内联函数往往是降低了函数的复用性,所以编译器在对内联函数作展开处理时除了检测用户定义的内联函数内部是否有指针/循环/递归外
//还会在函数执行效率和函数调用开销之间进行权衡,我们认为一个函数体积小而且被大量频繁调用,应该做内联展开时就可以使用static inline关键字修饰它
//但编译器会不会作内联展开也会有自己的权衡,如果你想告诉编译器一定要展开或者不作展开,就可以使用noinline或always_inline对函数作一个属性声明
//
//
//在这个程序中，我们分别定义两个内联函数 func() 和 print_num()，然后使用 always_inline 对 func() 函数进行属性声明。接下来， 我们对生成的可执行文件 a.out 作反汇编处理，其汇编代码如下
//
//$ arm-linux-gnueabi-gcc -o a.out inline.c
//$ arm-linux-gnueabi-objdump -D a.out
//00010438    <print_num>:
//10438:    e92d4800        push{ fp, lr }
//1043c:    e28db004        add fp, sp, #4
//10440:    e24dd008        sub sp, sp, #8
//10444:    e50b0008        str r0, [fp, # - 8]
//10448:    e51b1008        ldr r1, [fp, # - 8]
//1044c:    e59f000c        ldr r0, [pc, #12]
//10450:    ebffffa2        bl    102e0 <printf@plt>
//10454:    e1a00000        nop; (mov r0, r0)
//10458:    e24bd004        sub sp, fp, #4
//1045c:    e8bd8800        pop{ fp, pc }
//10460:    0001050c        andeq    r0, r1, ip, lsl #10
//
//00010464 <main>:
//10464:    e92d4800        push{ fp, lr }
//10468:    e28db004        add fp, sp, #4
//1046c:    e24dd008        sub sp, sp, #8
//10470:    e3a03003        mov r3, #3
//10474:    e50b3008        str r3, [fp, # - 8]
//10478:    e51b3008        ldr r3, [fp, # - 8]
//1047c:    e2833001        add r3, r3, #1
//10480:    e50b300c        str r3, [fp, # - 12]
//10484:    e3a0000a        mov r0, #10
//10488:    ebffffea        bl    10438 <print_num>
//1048c:    e3a03000        mov r3, #0
//10490:    e1a00003        mov r0, r3
//10494:    e24bd004        sub sp, fp, #4
//10498:    e8bd8800        pop{ fp, pc }
//
//通过反汇编代码可以看到因为我们对func()函数作了always_inline属性声明,所以编译器在编译过程中对于main()函数调用func()会直接在调用处展开
//10470:    e3a03003        mov r3, #3
//10474:    e50b3008        str r3, [fp, # - 8]
//10478:    e51b3008        ldr r3, [fp, # - 8]
//1047c:    e2833001        add r3, r3, #1
//10480:    e50b300c        str r3, [fp, # - 12]
//
//而对于print_num()函数虽然我们对其作了内联声明,但编译器并没有对其作内联展开,而是当作一个普通函数对待
//还有一个注意的细节是当编译器对内联函数作展开处理时,会直接在调用处展开内联函数的代码,不再给func()函数本身生成单独的汇编代码
//这是因为其它调用该函数的位置都作了内联展开,没必要再去生成,在这个例子中我们发现就没有给func()函数本身生成单独的汇编代码
//编译器只给print_num()函数生成了独立的汇编代码
//
//内联函数为什么常使用static修饰?
//在Linux内核中你会看到大量的内联函数定义在头文件中,而且常常使用static修饰
//为什么inline函数经常使用static修饰呢?这个问题在网上也讨论了很久,听起来各有道理,从C语言到C++
//甚至有人还拿出Linux内核作者Linus作者关于对static inline的解释
//我的理解是这样的,内联函数为什么要定义在头文件中呢?因为它是一个内联函数,可以像宏一样使用
//任何想使用这个内联函数的源文件不必亲自再去定义一遍,直接包含这个头文件,即可像宏一样使用,那为什么还要用static修饰呢?
//因为我们使用inline定义的内联函数,编译器不一定会内联展开,那么当多个文件都包含这个内联函数的定义时,编译时就有可能报重定义错误
//而使用static修饰可以将这个函数的作用域局限在各自本地文件内,避免了重定义错误,理解了这两点就能够看懂Linux内核头文件中定义的大部分内联函数了