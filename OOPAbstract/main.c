//
//  main.c
//  OOPAbstract
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

//typedef struct Person ClassA;

typedef void(*Method)(ClassA *my_self);//定义一个类型为void (Person *my_self)的函数指针,函数需要Person类型的指针,无返回

typedef struct Person
{
    char name[12];//属性
    int age;
    int sex;
    Method BehaviorOne;//行为
}ClassA;


void selfIntroducation(ClassA *my_self)
{
    printf("my name is %s,age %d,sex %d\n", my_self->name, my_self->age, my_self->sex);
}

int main(int argc, const char * argv[]){
    
    ClassA *pmst = (ClassA *)malloc(sizeof(ClassA));
    //pmst指针在调用malloc方法后返回分配的地址为0x12345678,会标识占sizeof(Person)个字节
    //pmst->age = 18其实是对0x12345678偏移12字节内存的赋值,占4个字节
    //函数在编译之后放置在代码段,入口为函数指针
    //pmst->behavior1(pmst);先取到0x12345678偏移20字节内存的值————函数指针,然后call命令调用
    //编译之后代码都变成了对内存地址的访问称之为静态绑定,那么该如何实现Runtime运行时的动态访问呢
    //比如在UI界面上(Terminal那种古老的输入输出方式也是OK的)输入一个类的名称以及调用方法名称,紧接着我们要实例化一个该类的对象,然后调用方法
    // 1.1
    strcpy(pmst->name, "pmst");
    pmst->age = 18;
    pmst->sex = 0;
    pmst->BehaviorOne = selfIntroducation;
    
    pmst->BehaviorOne(pmst);
    
    
    return 0;
}
