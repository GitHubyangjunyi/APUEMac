//
//  main.c
//  InlineAssembleFour
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int int_a = 0x12345678, int_b = 0;
    asm("movw %1,%0;" : "=m"(int_b) : "a"(int_a));//往int_b传入一个字,默认传入低字0x5678
    printf("Word int_b is 0x%x\n", int_b);
    int_b = 0;//将int_b恢复为0
    
    asm("movb %1,%0;" : "=m"(int_b) : "a"(int_a));//往int_b传入一个字节,默认传入低字节0x78
    printf("Low byte int_b is 0x%x\n", int_b);
    int_b = 0;//将int_b恢复为0
    
    asm("movb %h1,%0;" : "=m"(int_b) : "a"(int_a));//往int_b传入一个字节,使用h占位符,传入7~15位0x56
    printf("High byte int_b is 0x%x\n", int_b);
    int_b = 0;//将int_b恢复为0
    
}

//序号占位符之字长限定(机器模式相关)
//关于占位符
//假设我们用a指定寄存器为eax,我们在汇编代码中可以用eax作为操作数,但有时我们对寄存器的要求并不严格,使用哪个都可以
//所以我们可以用r来告诉gcc替我们自由安排,于是问题来了,由于r表示可以用6个寄存器之一,我们并不知道gcc为操作数分配了哪个寄存器
//或者我们对操作数用了内存约束,操作数没有名称可以引用,这时候我们在汇编代码中该如何引用操作数呢?
//为方便对操作数的引用,扩展内联汇编提供了占位符,它的作用是代表约束指定的操作数(寄存器/内存/立即数)
//我们更多的是在内联汇编中使用占位符来引用操作数,占位符分为序号占位符和名称占位符两种
//1.序号占位符
//序号占位符是对在output和input中的操作数,按照它们从左到右出现的次序,从0开始编号一直到9,也就是说最多支持10个序号占位符
//操作数用在assembly code中,引用它的格式是%0～9,在操作数自身的序号前面加1个百分号%,便是对相应操作数的引用
//一定要切记,占位符指代约束所对应的操作数,也就是在汇编中的操作数,并不是圆括号中的C变量,比如:
//
//asm("addl %%ebx,%%eax":"=a"(out_sum) : "a"(int_a), "b"(int_b));等价于
//asm("addl %2,%1":"=a"(out_sum) : "a"(int_a), "b"(int_b));
//
//"=a"(out_sum)序号为0,%0对应的是eax
//"a"(int_a)序号为1,%1对应的是eax
//"b"(int_b)序号为2,%2对应的是ebx
//
//由于扩展内联汇编中的占位符要有前缀%,为了区别占位符和寄存器,只好在寄存器前用两个%做前缀,解释了在扩展内联汇编中寄存器前面要有两个%做前缀的原因
//
//占位符所表示的操作数默认情况下为32位数据,指令的操作数大小并不一致,有的指令操作数大小是32位,有的是16位,有的是8位
//当为这些指令提供操作数时,编译器会自动取32位数据的低16位给需要16位操作数的指令,取32位的低8位给需要8位操作数的指令
//由于32位数据中,高16位设法直接使用,所以对于16位操作数只能取32位中的低16位,但对于8位操作数就不一样了
//尽管默认情况下会用低8位作为字节指令的操作数,但32位数据中能直接使用的字节不只是低8位,还有第8～15位
//所以对于宇节指令,gcc为我们提供了改变默认操作数的机会,我们可以自由选择是用0～7位,还是8～15位,这么说有点抽象
//拿32位的寄存器eax举例,其常用的部分是eax/ax/al(高16位没法直接用)
//有些指令的操作数是宇,所以用ax做操作数即可,有些指令操作数是字节,用al或ah都可以,默认情况下会将al当作操作数
//这时候我们可以在%和序号之间插入字符h来表示操作数为ah,或者插入字符b来表示操作数为al
//h和b限定属于机器模式中的内容,gcc允许在更细的粒度上指定数据宽度或数据的某部分
//
//2.名称占位符
//名称占位符与序号占位符不同,序号占位符靠本身出现在output和input中的位置就能被编译器辨识出来
//而名称占位序需要在output和input中把操作数显式地起个名字
//它用这样的格式来标识操作数:    [名称]"约束名"(C变量)
//这样该约束对应的汇编操作数便有了名字,在assembly code中引用操作数时,采用%[名称]的形式就可以了