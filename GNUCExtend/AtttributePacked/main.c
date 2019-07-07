//
//  main.c
//  AtttributePacked
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    //aligned属性一般用来增大变量的地址对齐,元素之间因为地址对齐会造成一定的内存空洞,而packed属性则与之相反用来减少地址对齐
    //用来指定变量或类型使用可能小的地址对齐方式
    struct data
    {
        char a;
        short b __attribute__((packed));
        int c __attribute__((packed));
    };
    struct data s;
    printf("data size: %d\n", sizeof(s));//7结构体内各个成员地址的分配使用小1字节的对齐方式导致整个结构体的大小只有7个字节
    printf("&s.a: %p\n", &s.a);//0
    printf("&s.b: %p\n", &s.b);//1
    printf("&s.c: %p\n", &s.c);//3
    //这个特性在底层驱动开发中还是非常有用的,比如你想定义一个结构体封装一个IP控制器的各种寄存器
    //在ARM芯片中每一个控制器的寄存器地址空间一般是连续存在的,如果考虑数据对齐,结构体内有空洞,这样就跟实际连续的寄存器地址不一致了
    //使用packed就可以避免这个问题,结构体的每个成员都紧挨着依次分配存储地址,这样就避免了各个成员元素因地址对齐而造成的内存空洞
    struct datap
    {
        char a;
        short b;
        int c;
    }__attribute__((packed));
    struct datap sp;
    printf("datap size: %d\n", sizeof(sp));//7结构体内各个成员地址的分配使用小1字节的对齐方式导致整个结构体的大小只有7个字节
    printf("&sp.a: %p\n", &sp.a);//0
    printf("&sp.b: %p\n", &sp.b);//1
    printf("&sp.c: %p\n", &sp.c);//3
    //我们对整个结构体添加packed属性和分别对每个成员添加packed属性效果是一样的
    //修改结构体后程序的运行结果跟上面程序运行结果相同——结构体的大小为7,结构体内各成员地址相同
    //在Linux内核中我们经常看到aligned和packed一起使用,即对一个变量或类型同时使用aligned和packed属性声明
    //这样做的好处是既避免了结构体内因地址对齐产生的内存空洞,又指定了整个结构体的对齐方式
    struct dataap
    {
        char a;
        short b;
        int c;
    }__attribute__((packed, aligned(8)));
    struct dataap sap;
    printf("dataap size: %d\n", sizeof(sap));//8
    printf("&sap.a: %p\n", &sap.a);//0
    printf("&sap.b: %p\n", &sap.b);//1
    printf("&sap.c: %p\n", &sap.c);//3
    //在这个程序中结构体dataap虽然使用packed属性声明,整个长度变为7
    //但是我们同时又使用了aligned(8)指定其按8字节地址对齐,所以编译器要在结构体后面填充1个字节,这样整个结构体的大小就变为8字节,按8字节地址对齐
    
    
    return 0;
}
