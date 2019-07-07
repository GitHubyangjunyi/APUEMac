//
//  main.c
//  ContainerOfMacro
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define offsetof(TYPE,MEMBER)   ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(PTR,TYPE,MEMBER)    ({  \
    const typeof(((TYPE *)0)->MEMBER) *__mptr = (PTR);  \
    (TYPE *)((char *)__mptr - offsetof(TYPE, MEMBER)); })

struct student
{
    int age;
    int num;
    int math;
};

void test(int *x);

int main(int argc, const char * argv[]) {
    

    struct student stu =
    {
        .age = 1,
        .num = 22,
        .math = 333,
    };
    
    struct student *px;
    
    px = container_of(&stu.num, struct student, num);
    
    printf("%d\n", px->age);//1
    printf("%d\n", px->num);//22
    printf("%d\n", px->math);//333
    
    test(&stu.age);
    
    printf("%d\n", px->age);//4
    printf("%d\n", px->num);//5
    printf("%d\n", px->math);//6
    
    
    
    
    
    return 0;
}

void test(int *x)//注意:这里需要传入指针而不是值拷贝,不然修改将不生效
{
    struct student *p;
    p = container_of(x, struct student, age);
    //对结构体进行改动
    p->age = 4;
    p->num = 5;
    p->math = 6;
    printf("%d\n", p->age);//4
    printf("%d\n", p->num);//5
    printf("%d\n", p->math);//6
}
