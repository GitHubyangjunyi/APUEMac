//
//  main.c
//  ContainerOfMacroPre
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

//最后看这里
//内核的list核心链表关键的实现就是container_of宏,理解这个宏更有助于我们学习list链表
//内核的list核心链表关键的实现就是container_of宏,理解这个宏更有助于我们学习list链表
//内核的list核心链表关键的实现就是container_of宏,理解这个宏更有助于我们学习list链表
//container_of宏:
//根据结构体某一成员的地址获取这个结构体的首地址,之后定义一个该结构类型的指针变量接收这个首地址以访问结构体的其他成员
//这个宏在内核中非常重要,Linux内核驱动中为了抽象,对数据结构体进行了多次封装,往往一个结构体里面嵌套多层结构体
//(个人想法:总不能用到一个结构体就把最外层的最大结构体指针传进去吧,用到哪一层就获取哪一层的结构体)
//也就是说内核驱动中不同层次的子系统或模块使用的是不同封装程度的结构体,这也是C语言的面向对象思想
//
//#define offsetof(TYPE,MEMBER)   ((size_t) &((TYPE *)0)->MEMBER)
//#define container_of(PTR,TYPE,MEMBER)    ({  \
//    const typeof(((TYPE *)0)->MEMBER) *__mptr = (PTR);  \
//    (TYPE *)((char *)__mptr - offsetof(TYPE, MEMBER)); })
//
//宏有三个参数:
//    type:结构体类型
//    member:结构体成员
//    ptr:结构体成员member的地址
//也就是说我们知道了一个结构体的类型,结构体内某一成员的地址就可以直接获得到这个结构体的首地址
//container_of宏返回的就是这个结构体的首地址

//然后看这里
#define offsetof(TYPE,MEMBER)   ((size_t) &((TYPE *)0)->MEMBER)
//上面的宏计算结构体某个成员在结构体内的偏移
//这个宏有两个参数一个是结构体类型TYPE,一个是结构体的成员MEMBER
//它使用的技巧跟我们计算0地址常量指针的偏移是一样的
//将0强制转换为一个指向TYPE的结构体常量指针,然后通过这个常量指针访问成员,获取成员MEMBER的地址
//其大小在数值上就等于MEMBER在结构体TYPE中的偏移

//再然后看这里
//因为结构体的成员数据类型可以是任意数据类型,所以为了让这个宏兼容各种数据类型我们定义了一个临时指针变量__mptr
//该变量用来存储结构体成员MEMBER的地址,即存储ptr的值,那如何获取ptr指针类型?
//    typeof(((TYPE *)0)->MEMBER) *__mptr = (PTR);//获得ptr指针类型
//宏的参数ptr代表的是一个结构体成员变量MEMBER的地址,所以ptr的类型是一个指向MEMBER数据类型的指针

#define container_of(PTR,TYPE,MEMBER)    ({  \
    const typeof(((TYPE *)0)->MEMBER) *__mptr = (PTR);  \
    (TYPE *)((char *)__mptr - offsetof(TYPE, MEMBER)); })

//后一句的意义就是拿结构体某个成员member的地址减去这个成员在结构体type中的偏移,结果就是结构体type的首地址
//char指针减法只移一个字节
//最后强制转换成(TYPE *)类型

struct student
{
    int age;
    int num;
    int math;
};

int main(int argc, const char * argv[]) {
    
    
    //先从这里看
    struct student stu = { 20, 1111, 99 };
    printf("&stu = %p\n", &stu);
    printf("&stu.age = %p\n", &stu.age);
    printf("&stu.num = %p\n", &stu.num);
    printf("&stu.math = %p\n", &stu.math);
    
    //计算成员变量在结构体中的偏移
    printf("&age = %p\n", &((struct student*)0)->age);//将数字0通过强制类型转换为一个指向结构体类型为student的常量指针
    printf("&num = %p\n", &((struct student*)0)->num);//分别打印这个常量指针指向的结构体的各成员地址
    printf("&math= %p\n", &((struct student*)0)->math);
    //常量指针为0即可以看做结构体首地址为0,所以结构体中每个成员变量的地址即为该成员相对于结构体首地址的偏移0 4 8
    //有了上面的基础我们再去分析container_of宏的实现就比较简单了
    //知道了结构体成员的地址如何去获取结构体的首地址？
    //很简单直接拿结构体成员的地址减去该成员在结构体内的偏移就可以得到该结构体的首地址了
    //container_of宏是有一个语句表达式构成,最后一个表达式就是最终的值
    
    
    return 0;
}
