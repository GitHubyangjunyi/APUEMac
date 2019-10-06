//
//  main.c
//  SetjmpImplementation
//
//  Created by 杨俊艺 on 2019/9/22.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

int my_func(int a, int b) {
    if (b == 0) {
        printf("do not allow division by 0\n");
        longjmp(env, 1);
    }
    return a / b;
}

int main(int argc, const char * argv[]) {
    int res = setjmp(env);
    if (res == 0) {
        printf("return from setjmp\n");
        my_func(10, 0);
    } else {
        printf("return from longjmp: %d\n", res);
    }
    return 0;
    
}

//以下的源代码取自musl libc
//setjmp的代码是这样的
//
//setjmp:
//1   mov    4(%esp), %eax    // eax = jmp_buf
//2   mov    %ebx, (%eax)     // jmp_buf[0] = ebx
//3   mov    %esi, 4(%eax)    // jmp_buf[1] = esi
//4   mov    %edi, 8(%eax)    // jmp_buf[2] = edi
//5   mov    %ebp, 12(%eax)   // jmp_buf[3] = ebp
//6   lea    4(%esp), %ecx
//7   mov    %ecx, 16(%eax)   // jmp_buf[4] = esp+4
//8   mov    (%esp), %ecx
//9   mov    %ecx, 20(%eax)   // jmp_buf[5] = *esp
//0   xor    %eax, %eax       // eax = 0
//10  ret                     // return eax
//
//栈的信息在进入setjmp之时栈是这样的
//-----------------------high
//  参数:jmp_buf
//-----------------------
//  调用者下一条指令的地址   <-- esp
//-----------------------low
//第1行将esp向上偏移4字节取得jmp_buf,赋值给eax
//第2行保存ebx  jmp_buf[0] = ebx
//第3行保存esi  jmp_buf[1] = esi
//第4行保存edi  jmp_buf[2] = edi
//第5行保存ebp  jmp_buf[3] = ebp
//第6~7行保存栈顶前一个地址
//            jmp_buf[4] = esp+4    也就是jmp_buf参数那一行的栈地址
//第8~9行保存栈顶的值
//            jmp_buf[5] = *esp     也就是调用者函数下一条指令的地址
//第10~11行eax清零,函数返回,相当于返回0
//ret指令和call相反,从栈顶弹出调用者函数下一条指领的地址然后跳过去,最后的栈信息是这样的
//-----------------------high
//  jmp_buf参数           <-- esp
//-----------------------low
//setjmp完成后jmp_buf保存了这些信息
//
//[ebx, esi, edi, ebp, esp, eip]
//
//longjmp:
//1     mov  4(%esp),%edx // edx = jmp_buf
//2     mov  8(%esp),%eax // eax = val
//3     test    %eax,%eax // val == 0?
//4     jnz 1f
//5     inc     %eax      //  eax++
//6  1:
//7     mov   (%edx),%ebx // ebx = jmp_buf[0]
//8     mov  4(%edx),%esi // esi = jmp_buf[1]
//9     mov  8(%edx),%edi // edi = jmp_buf[2]
//10    mov 12(%edx),%ebp // ebp = jmp_buf[3]
//11    mov 16(%edx),%ecx // ecx = jmp_buf[4]
//12    mov     %ecx,%esp // esp = ecx
//13    mov 20(%edx),%ecx // ecx = jmp_buf[5]
//14    jmp *%ecx         // eip = ecx
//longjmp需要传递两个参数,所以调用longjmp时的栈信息是这样的
//-----------------------high
//  参数2：整型值
//-----------------------
//  参数1：jmp_buf
//-----------------------
//  调用者下一条指令的地址   <-- esp
//-----------------------low
//第1行取得jmp_buf指针保存到edx
//第2行取得val保存到eax
//第3~5行判断val是否为0,如果是则要加1,因为setjmp返回0会走正常流程,这样就死循环了
//第7~10行,从jmp_buf恢复各个寄存器的值
//第11~12行从jmp_buf恢复esp的值,此时的esp就是在setjmp返回时的那个栈顶地址
//第13行获得setjmp时,调用者函数下一条指令的地址
//第14行跳到这个地址去
//在第14行执行后,执行流程就跳到setjmp的返回处,并且因为eax被设置成了val所以返回值也变成val
//
//http://git.musl-libc.org/cgit/musl/tree/src/setjmp/i386
//https://zhuanlan.zhihu.com/p/82492121?utm_source=qq&utm_medium=social&utm_oi=579636299762372608
