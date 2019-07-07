//
//  main.c
//  BitField
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    //unsigned int isOpen : 1; //编译无法通过
    
    struct packed_struct {
        unsigned int f1 : 1;
        unsigned int f2 : 1;
        unsigned int f3 : 1;
        unsigned int f4 : 1;
        unsigned int type : 4;
        unsigned int my_int : 9;
    } pack;
    //C尽可能紧凑地自动打包上述位字段,前提是字段的最大长度小于或等于计算机的整数字长
    //如果不是这种情况,那么一些编译器可能允许字段存储器重叠,而其他编译器会将下一个字段存储在下一个字中
    printf("%d\n", (int) sizeof(struct packed_struct));
    
    
    
    
    return 0;
}

//内存紧张的时候可以使用位域定义结构体成员变量,比如当我们需要定义一个表示true或false的时候
//如果想这样定义    int isOpen;很浪费空间
