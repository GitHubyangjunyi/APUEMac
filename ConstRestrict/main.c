//
//  main.c
//  ConstRestrict
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

typedef int* p_int;

int main(int argc, const char * argv[]) {
    
    const double e = 2.71828182845905;
    const char msg[] = "warning";
    
    //如果const后面是一个类型,则跳过最近的原子类型修饰后面的数据
    //原子类型:int/short/char.../typedef定义的类型
    
    int a = 1;
    int b = 100;
    
    int const *p1 = &a;//const后面是*p1,实质上是数据a,则修饰*p1,通过p1不能修改a的值,但p1指向可以改变
    //*p1 = 100;//错误类型:表达式必须是可修改的左值
    p1 = &b;//p1指向可以改变
    
    const int *p2 = &a;//const后面是int类型,则跳过int修饰*p2,效果同上
    //*p2 = 100;//错误类型:表达式必须是可修改的左值
    p2 = &b;//p2指向可以改变
    
    
    int * const p3 = NULL;//const后是数据p3,也就是p3本身是const
    //p3 = &a;//错误类型:表达式必须是可修改的左值
    *p3 = 999;
    
    const int * const p4 = &a;//通过p4不能改变a的值,同时p4本身也是const
    //*p4 = 888;//错误类型:表达式必须是可修改的左值
    //p4 = &b;//错误类型:表达式必须是可修改的左值
    
    int const * const p5 = &a;//同上
    //*p5 = 888;//错误类型:表达式必须是可修改的左值
    //p5 = &b;//错误类型:表达式必须是可修改的左值
    
    const p_int px = &a;//const跳过类型p_int修饰px,指针px本身也是const
    *px = 666;
    //px = &b;//错误类型:表达式必须是可修改的左值
    
    p_int const px2 = &a;//const直接修饰px2,同上
    
    p_int const *px3 = &a;
    //*px3 = 888;//错误类型:表达式必须是可修改的左值
    px3 = &b;
    
    return 0;
}

//任何变量的声明都可以使用const限定符限定,该限定符指定变量的值不能被修改,对数组而言,const限定符指定数组所有元素的值都不能被修改
//const限定符也可以配合数组参数使用,表明函数不能修改数组元素的值
//    int strlen(const char[] );
//如果试图修改const限定符限定的值,取决于具体的实现
