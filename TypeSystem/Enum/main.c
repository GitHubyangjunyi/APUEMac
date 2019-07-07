//
//  main.c
//  Enum
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    enum months
    {
        JAN=1,
        FEB,
        MAR,
        APR,
        MAY,
        JUN,
        JUL,
        AUG,
        SEP,
        OCT,
        NOV,
        DEC
    };
    
    printf("%d\n", JAN);
    printf("%d\n", FEB);
    printf("%d\n", MAR);
    printf("%d\n", APR);
    printf("%d\n", MAY);
    printf("%d\n", JUN);
    printf("%d\n", JUL);
    printf("%d\n", AUG);
    printf("%d\n", SEP);
    printf("%d\n", OCT);
    printf("%d\n", NOV);
    printf("%d\n", DEC);
    
    enum months clearmonth = MAY;
    printf("clearmonth = %d\n", clearmonth);
    
    
    
    return 0;
}

//枚举类型在没有显示说明的情况下,第一个枚举名的值为0,第二个为1,依次类推
//如果只指定了部分枚举值,那么未指定值的枚举名将依着最后一个指定值向后递增
//不同枚举中的名字必须互不相同,同一枚举中不同的名字可以具有相同值
//
//枚举为建立常量值与名字之间的关联提供了一种便利的方式,相对于#define来说,优势在于常量值可以自动生成
//尽管可以声明enum类型的变量,但编译器不检查这种类型中的变量中存储的值是否为该枚举的有效值
//不过枚举变量提供这种检查,因此枚举比#define更具优势,调试程序可以以符号形式打印出枚举变量的值
