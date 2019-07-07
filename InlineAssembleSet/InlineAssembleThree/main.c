//
//  main.c
//  InlineAssembleThree
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int int_a = 1, int_b = 2;
    printf("int_b=%d\n", int_b);//输出2
    asm("movb %b0,%1;" : : "a"(int_a), "m"(int_b));//%1是序号占位符,可认为它代表int_b的内存地址(指针),约束m告诉gcc把变量int_b的指针作为内联代码的操作数
    printf("int_b=%d\n", int_b);//输出1
    //对寄存器eax的引用:%b0,这是用的32位数据的低8位,在这里就是指al寄存器,如果不显式加字符b,编译器也会按照低8位来处理
    //但它会发出警告:    Warning: using ’%al’instead of %eax’due to 'b'suffix
}

//内存约束
//内存约束是要求gcc直接将位于input和output中的C变量的内存地址作为内联汇编代码的操作数,不需要寄存器做中转
//直接进行内存读写,也就是汇编代码的操作数是C变量的指针
//m:表示操作数可以使用任意一种内存形式
//o:操作数为内存变量,但访问它是通过偏移量的形式访问,即包含offset_address的格式
