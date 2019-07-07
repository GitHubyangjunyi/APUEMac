//
//  main.c
//  InlineAssembleEight
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    //本文件的功能是打印字符串Hello,World回车,然后再打印出printf的返回值
    //正常情况下printf会返回打印的字符数,hello,world\n共12个字符
    int ret_cnt = 0, test = 0;//test是演示用的,用它来干扰返回值,没实际意义
    char* fmt = "Hello,World\n";//12个字符
    asm("pushl %1;        \
        call printf;    \
        addl $4,%%esp;    \
        movl $6,%2"        \
        :"=&a"(ret_cnt)    \
        : "m"(fmt), "r"(test)    \
        );
    printf("The number of bytes written is %d\n", ret_cnt);//按预期输出12
    if (ret_cnt != 12)
    {
        printf("返回值被破坏!");
    }
    else
    {
        printf("返回值完整!");
    }
    
    return 0;
}

//损坏通知二
//修饰符＆就派上用场了,只要为test约束的寄存器不要和ret_ent相同就行
//＆:表示此output中的操作数要独占所约束(分配)的寄存器,只供output使用,任何input中所分配的寄存器不能与此相同
//注意,当表达式中有多个修饰符时,＆要与约束名挨着,不能分隔
//
//
//内存约束m把字符串指针fmt传给了汇编代码,把变量test用寄存器约束r声明,由gcc自由分配寄存器
//将第4行定义的字符串指针fmt通过压栈传参给printf函数,执行后,eax寄存器中值是printf的返回值,应该为12
//然后回收参数所占的栈空间
//接着把立即数6传入了gcc为变量test分配的寄存器,为了验证是不是分配的eax
//output部分中的C变量ret_cnt获得了寄存器的值
//addl $4,%%esp;    回收栈空间
//movl $6,%2        把立即数6传入了gcc为变量test分配的寄存器
//output部分中的C变量ret_ent获得了寄存器的值
