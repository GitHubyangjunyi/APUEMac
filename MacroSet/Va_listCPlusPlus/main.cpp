//
//  main.cpp
//  Va_listCPlusPlus
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <iostream>
constexpr auto END = -1;//相当于#define END -1

double average(const int count, ...)
{
    va_list ap;            //定义一个va_list类型的变量(参数列表)
    int i;                //定义一个可以在下方循环使用的整型变量
    double total = 0.0;    //定义一个浮点数保存所有的参数的和
    
    va_start(ap, count);//在这里获得可变参数列表的第一个参数的地址
    //括号里面第一个参数是类型为va_list的指针,第二个参数是可变类型最左边的参数,此处是count
    //函数传递参数的过程就是将函数的参数从右向左逐次压栈,func(int i, char c, doube d)
    //这个函数传递参数的过程就是将d/c/i逐次压到函数的栈中,由于栈是从高地址向低地址扩展的,所以d的地址最高,i的地址最低
    
    for (i = 0; i < count; ++i)
    {
        total += va_arg(ap, double);//在这里返回可变的参数,括号里面第二个参数是想要返回的参数类型
    }
    va_end(ap);//在这里可以清空可变参数列表va_list
    
    return total / count;
}

int va_sum(int first_num, ...)
{
    //定义参数列表
    va_list ap;
    //初始化参数列表
    va_start(ap, first_num);
    int result = first_num, temp = 0;
    
    while ((temp=va_arg(ap,int)) !=END)//判断返回参数是否等于结束标志
    {
        result += temp;
    }
    
    va_end(ap);//关闭参数列表
    
    return result;
}


int main(int argc, const char * argv[]) {

    printf("average函数测试:\n");
    printf("The value of avarage is %lg\n", average(3, 7.3, 9.5, 8.5));    //结果为8.43333?
    printf("The value of avarage is %lg\n", average(2, 4.6, 5.4));        //结果为5?
    
    printf("va_sum函数测试:\n");
    printf("%d\n", va_sum(1, 2, 3, 4, 5, END));
    printf("%d\n", va_sum(1, 2, 3, 4, END));
    printf("%d\n", va_sum(1, 2, 3, 4, 5.0, END));//出错
    
    return 0;
}

//三宏一类型:
//    三个宏
//        va_start    va_arg        va_end
//    一个类型
//        va_list
//
//void va_start(va_list ap, v);        功能:初始可变参数列表;        ap:可变参数列表地址        v:确定的参数
//type va_arg(va_list ap, t);        功能:返回下一个参数的列表
//void va_end(va_list ap);            功能:关闭参数列表,即把ap置空
//
//
//使ap指向第一个可变参数的地址
//#define  va_start(ap, v)     (ap = (va_list)&v + _INTSIZEOF(v))
//
//使ap指向下一个可变参数,同时将目前ap所指向的参数提取出来并返回
//#define  va_arg(ap, t)       (*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
//
//销毁ap
//#define  va_end(ap)         (ap = (va_list)0)
