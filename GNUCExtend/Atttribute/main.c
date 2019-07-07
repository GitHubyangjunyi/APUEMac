//
//  main.c
//  Atttribute
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

static int  global_val __attribute__((section(".data")));//全局变量才能定义在.data段

int main(int argc, const char * argv[]) {
    
    char c __attribute__((aligned(8))) = 4;
    char c1 __attribute__((packed, aligned(4)));
    char c2 __attribute__((packed, aligned(4))) = 4;
    __attribute__((packed, aligned(4))) char c3 = 4;
    
    
    
    return 0;
}

//atttribute这个关键字用来声明一个函数/变量或类型的特殊属性,指导编译器在编译程序中进行特定方面的优化或代码检查
//比如我们可以使用属性声明来指定某个变量的边界对齐方式
//attribute的使用非常简单,当我们定义一个函数/变量或类型时直接在它们名字旁边添加下面的属性声明即可
//__atttribute__((ATTRIBUTE))
//这里需要注意的是attribute后面是两对小括号,不能图方便只写一对,否则编译可能通不过
//括号里面的ATTRIBUTE代表的就是要声明的属性,现在attribute支持十几种属性:
//section
//aligned
//packed
//format
//weak
//alias
//noinline
//always_inline
//...
//有些属性可能还有自己的参数,比如aligned(8)表示这个变量按8字节地址对齐,参数也要使用小括号括起来
//如果属性的参数是一个字符串,小括号里的参数还要用双引号引起来
//我们也可以对一个变量同时添加多个属性说明,在定义时各个属性之间用逗号隔开就可以了
//在上面的示例中我们对一个变量添加2个属性声明,这两个属性都放在atttribute(())的2对小括号里面,属性之间用逗号隔开
//这里还有一个细节就是属性声明要紧挨着变量,上面的三种定义方式都是没有问题的,但下面的定义方式在编译的时候可能就通不过
//char c2 = 4 __attribute__((packed, aligned(4)));
