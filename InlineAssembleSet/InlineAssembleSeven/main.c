//
//  main.c
//  InlineAssembleSeven
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    //打印字符串Hello,World回车,然后再打印出printf的返回值
    //正常情况下printf会返回打印的字符数,hello,world\n共12个字符
    int ret_cnt = 0, test = 0;//test是演示用的,用它来干扰返回值,无实际意义
    char* fmt = "Hello,World\n";//12个字符
    asm("pushl %1;        \
        call printf;    \
        addl $4,%%esp;    \
        movl $6,%2"        \
        :"=a"(ret_cnt)    \
        : "m"(fmt), "r"(test)    \
        );
    printf("The number of bytes written is %d\n", ret_cnt);//未按预期输出12,输出6
    if (ret_cnt != 12)
    {
        printf("返回值被破坏!");
    }
    else
    {
        printf("返回值完整!");
    }
    
}

//损坏通知一
//修饰符＆用来表示此寄存器只能分配给output中的某个C变量使用,不能再分给input中某变量了,函数执行完成时,返回值会存储在寄存器eax中
//通常我们会将返回值获取到C变量中再处理,如果是让gcc自由分配寄存器,gcc有可能把eax分配出去另做他用
//有可能的一种情况是先调用函数,函数返回后又执行了其他操作,这个操作中用到了gcc分配的eax寄存器,于是函数的返回值便被破坏
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
