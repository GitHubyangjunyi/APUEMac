//
//  main.c
//  BuiltinLikelyUnLikely
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int a;
    scanf("%d", &a);
    if (a == 0)
    {
        printf("%d\n", 1);
        printf("%d\n", 2);
        printf("\n");
    }
    else
    {
        printf("%d\n", 5);
        printf("%d\n", 6);
        printf("\n");
    }
    
    return 0;
}

//Linux内核中使用__builtin_expect内建函数定义了两个宏
//    #define likely(x) __builtin_expect(!!(x),1)
//    #define unlikely(x) __builtin_expect(!!(x),0)
//
//这两个宏的主要作用就是告诉编译器:某一个分支发生的概率很高,或者很低基本不可能发生,编译器就根据这个提示信息去做一些分支预测的编译优化
//在这两个宏定义有一个细节,就是对宏的参数x做两次取非操作,这是为了将参数x转换为布尔类型,然后与1和0作比较,告诉编译器x为真或为假的可能性很高
//我们接下来举个例子让大家感受下,使用这两个宏后,编译器在分支预测上的一些编译变化
//在这个程序中，根据我们输入变量 a 的值，程序会执行不同的分支代码。我们接着对这个程序反汇编，生成对应的汇编代码。
//$ arm-linux-gnueabi-gcc expect.c
//$ arm-linux-gnueabi-objdump -D a.out
//00010558 <main>:
//10558:        e92d4800    push{ fp, lr }
//1055c:        e28db004    add fp, sp, #4
//10560:        e24dd008    sub sp, sp, #8
//10564:        e59f308c    ldr r3, [pc, #140]
//10568:        e5933000    ldr r3, [r3]
//1056c:        e50b3008    str r3, [fp, # - 8]
//10570:        e24b300c    sub r3, fp, #12
//10574:        e1a01003    mov r1, r3
//10578:        e59f007c    ldr r0, [pc, #124]
//1057c:        ebffffa5    bl    10418 <__isoc99_scanf@plt>
//10580:        e51b300c    ldr r3, [fp, # - 12]
//10584:        e3530000    cmp r3, #0
//10588:        1a000008    bne 105b0 <main + 0x58>
//1058c:        e3a01001    mov r1, #1
//10590:        e59f0068    ldr r0, [pc, #104]
//10594:        ebffff90    bl    103dc <printf@plt>
//10598:        e3a01002    mov r1, #2
//1059c:        e59f005c    ldr r0, [pc, #92]
//105a0:        ebffff8d    bl    103dc <printf@plt>
//105a4:        e3a0000a    mov r0,    #10
//105a8:        ebffff97    bl    1040c <putchar@plt>
//105ac:        ea000007    b    105d0 <main + 0x78>
//105b0:        e3a01005    mov r1, #5
//105b4:        e59f0044    ldr r0, [pc, #68]
//105b8:        ebffff87    bl    103dc <printf@plt>
//105bc:        e3a01006    mov r1, #6
//105c0:        e59f0038    ldr r0, [pc, #56]
//105c4:        ebffff84    bl    103dc <printf@plt>
//
//观察main函数的反汇编代码我们看到,汇编代码的结构就是基于我们的if/else分支先后顺序,依次生成对应的汇编代码
//看10588:bne 105b0 跳转
//我们接着改一下代码使用unlikely修饰if分支,告诉编译器这个if分支小概率发生,或者说不可能发发生
//
//int main(void)
//{
//    int a;
//    scanf("%d", &a);
//    if (unlikely(a == 0))
//    {
//        printf("%d", 1);
//        printf("%d", 2);
//        printf("\n");
//    }
//    else
//    {
//        printf("%d", 5);
//        printf("%d", 6);
//        printf("\n");
//    }
//    return 0;
//}
//
//对这个程序添加-O2优化参数编译,并对生成的可执行文件a.out反汇编
////$ arm-linux-gnueabi-gcc -O2 expect.c
//$ arm-linux-gnueabi-objdump -D a.out
//
//00010438 <main>:
//10438:        e92d4010    push    {r4, lr}
//1043c:        e59f4080    ldr r4, [pc, #128]
//10440:        e24dd008    sub sp, sp, #8
//10444:        e5943000    ldr r3, [r4]
//10448:        e1a0100d    mov r1, sp
//1044c:        e59f0074    ldr r0, [pc, #116]
//10450:        e58d3004    str r3, [sp, #4]
//10454:        ebfffff1    bl    10420 <__isoc99_scanf@plt>
//10458:        e59d3000    ldr r3, [sp]
//1045c:        e3530000    cmp r3, #0
//10460:        0a000010    beq 104a8 <main+0x70>
//10464:        e3a02005    mov r2, #5
//10468:        e59f105c    ldr r1, [pc, #92]
//1046c:        e3a00001    mov r0, #1
//10470:        ebffffe7    bl    10414 <__printf_chk@plt>
//10474:        e3a02006    mov r2, #6
//10478:        e59f104c    ldr r1, [pc, #76]
//1047c:        e3a00001    mov r0, #1
//10480:        ebffffe3    bl    10414 <__printf_chk@plt>
//10484:        e3a0000a    mov r0, #10
//10488:        ebffffde    bl    10408 <putchar@plt>
//1048c:        e59d2004    ldr r2, [sp, #4]
//10490:        e5943000    ldr r3, [r4]
//10494:        e3a00000    mov r0, #0
//10498:        e1520003    cmp r2, r3
//1049c:        1a000007    bne 104c0 <main + 0x88>
//104a0:        e28dd008    add sp, sp, #8
//104a4:        e8bd8010    pop{ r4, pc }
//104a8:        e3a02001    mov r2, #1
//104ac:        e59f1018    ldr r1, [pc, #24]
//104b0:        e1a00002    mov r0, r2
//104b4:        ebffffd6    bl    10414 <__printf_chk@plt>
//104b8:        e3a02002    mov r2, #2
//104bc:        eaffffed    b    10478 <main + 0x40 >
//
//我们对if分支条件表达式使用unlikely修饰,告诉编译器这个分支小概率发生,在编译器开启优化编译条件下,通过生成的反汇编代码
//10460:        0a000010    beq 104a8 <main+0x70>
//我们可以看到编译器将小概率发生的if分支汇编代码放在了后面,将else分支的汇编代码放在了前面,这样就确保了程序在执行时大部分时间都不需要跳转
//直接按顺序执行下面大概率发生的分支代码
