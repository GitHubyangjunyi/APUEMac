//
//  main.c
//  InlineAssembleTwo
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int int_a = 1, int_b = 2, out_sum;

int main(int argc, const char * argv[]) {
    
    //基本内联汇编,两数相加
    asm("pusha;                \
        movl int_a,%eax;    \
        movl int_b,%ebx;    \
        addl %ebx,%eax;        \
        mov %eax,out_sum;    \
        popa                ");
    printf("out_sum=%d\n", out_sum);//3
    
    //扩展内联汇编,两数相加,如果使用扩展内联汇编,变量可以是局部变量
    int int_c = 10, int_d = 20, out_sumx;
    asm("addl %%ebx,%%eax" : "=a"(out_sumx) : "a"(int_c), "b"(int_d));//约束名a为C变量int_a指定寄存器eax, 约束名b为C变量int_b指定用寄存器ebx
    printf("out_sum=%d\n", out_sumx);//30
}

//寄存器约束
//在基本内联汇编中的寄存器用单个%做前缀,在扩展内联汇编中单个%用来表示占位符,所以在扩展内联汇编中的寄存器前面用两个%做前缀
//asm [volatile] （"assembly code" : output : input : clobber/modify)
//asm("addl %%ebx,%%eax":"=a"(out_sum) : "a"(int_a), "b"(int_b));
//同样是为加法指令提供参数,int_a和int_b是在input部分输入的,用约束名a为C变量int_a指定寄存器eax,用约束名b为C变量int_b指定用寄存器ebx
//addl指令的结果保存到了eax,在output中用约束名a指定了把eax中的值存储到C变量out_sum中
//output中的=号是操作数类型修饰符,表示只写,其实就是out_sum=eax的意思
//1.寄存器约束
//寄存器约束就是要求gcc使用哪个寄存器,将input或output中变量约束在某个寄存器中,常见的寄存器约束有:
//a;表示寄存器 eax/ax/al
//b:表示寄存器 ebx/bx/bl
//c;表示寄存器 ecx/cx/cl
//d:表示寄存器 edx/dx/dl
//D:表示寄存器 edi/di
//S:表示寄存器 esi/si
//q:表示任意这4个通用寄存器之－:eax/ebx/ecx/edx
//r:表示任意这6个通用寄存器之一:eax/ebx/ecx/edx/esi/edi
//g:表示可以存放到任意地点(寄存器和内存),相当于除了同q一样外,还可以让gcc安排在内存中
//A:把eax和edx组合成64位整数
//f:表示浮点寄存器
//t:表示第1个浮点寄存器
//u:表示第2个浮点寄存器
//在内嵌64位汇编指令时应注意约束符的使用,因为有的约束符限定的是32位的寄存器
