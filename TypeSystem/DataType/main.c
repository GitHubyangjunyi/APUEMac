//
//  main.c
//  DataType
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <limits>//ANSI C标准规定,各种类型的取值范围必须定义在这个头文件中
#include <stdint.h>//C99新增,详情见C Primer Plus Stephen Prata 著 3.4.5节可移植类型
#include <inttypes.h>//C99新增

int main(int argc, const char * argv[]) {
    
    //关于溢出,溢出行为是未定义的
    int i = 2147483647;          //0111 1111 1111 1111 1111 1111 1111 1111
    unsigned int ui = 4294967295;//1111 1111 1111 1111 1111 1111 1111 1111
    
    printf("%d\t    %d\t    %d\n", i, i + 1, i + 2);//2147483647 -2147483648 -2147483647,超过最大值的情况下,int型从-2147483648继续(这一点涉及到补码)
    
    printf("%u\t    %u\t    %u\n", ui, ui + 1, ui + 2);//4294967295              0               1,超过最大值的情况下,unsigned int型从0继续
    
    return 0;
}

//在C语言中,用int关键字来表示基本的整数类型,后3个关键字long/short/unsigned和新增的signed用于提供基本整数类型的变式,如unsigned short int和long long int
//char关键字用于指定字母和其他字符,如#$%*,另外char类型也可以表示较小的整数
//float/double/long double表示带小数点的数
//_Bool类型表示布尔值true/false
//_Complex和_Imaginary分别用于表示复数和虚数
//通过这些关键字创建的类型,按计算机的存储方式可以分为两大基本类型:整数类型和浮点类型
//
//int类型是有符号整型,C语言把大多数整型常量视为int类型,但是非常大的整数除外
//short int(简写short)占用的存储空间可能小于int,short int也是有符号
//
//long int或long占用的存储空间可能大于int,long也是有符号
//
//long long int或long long(C99标准加入)占用的存储空间可能比long多,该类型至少占用64位,long long也是有符号
//
//unsigned int或unsigned只用于非负值场合
//
//在C90标准中添加了unsigned long int    或    unsigned long
//                   unsigned int            或    unsigned short
//
//C99标准又添加了unsigned long long int    或    unsigned long long
//
//在任何有符号类型的前面添加关键字signed可强调使用有符号类型的意图,例如short/short int/signed short/signed short int都表示同一种类型
//
//C标准对基本数据类型仅仅规定了允许的最小大小
//更多类型详解见C Primer Plus Stephen Prata 著 3.4节 C语言基本数据类型
