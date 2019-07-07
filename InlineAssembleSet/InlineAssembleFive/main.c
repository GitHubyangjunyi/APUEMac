//
//  main.c
//  InlineAssembleFive
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    //18除以3
    int int_a = 18, int_b = 3, out = 0;
    asm("divb %[divisor];movb %%al,%[result]"   \
        :[result]"=m"(out)                      \
        : "a"(int_a), [divisor]"m"(int_b)
        );
    printf("result is %d\n", out);//6
    
}

//名称占位符
//名称占位符与序号占位符不同,序号占位符靠本身出现在output和input中的位置就能被编译器辨识出来
//而名称占位序需要在output和input中把操作数显式地起个名字
//它用这样的格式来标识操作数:    [名称]"约束名"(C变量)
//这样该约束对应的汇编操作数便有了名字,在assembly code中引用操作数时,采用%[名称]的形式就可以了
//
//被除数int_a通过寄存器约束a存入寄存器eax
//除数int_b通过内存约束m被gcc将自己的内存地址传给汇编做操作数,咱们不用关心此内存地址是哪里
//为了引用除数所在的内存,我们用名称占位符divisor标识它
//除法指令divb可以通过%[divisor]引用除数所在的内存
//进行除法运算,divb是8位除法指令,余数存放在寄存器ah中,商存放在寄存器al中
//用movb指令将寄存器al的值写入用于存储结果的C变量out的地址中
