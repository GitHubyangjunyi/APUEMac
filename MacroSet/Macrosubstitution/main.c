//
//  main.c
//  Macrosubstitution
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define PRINT(FORMAT,VALUE) printf("The value is "FORMAT"\n",VALUE)//这种技巧只有当字符串常量作为宏参数给出时才能使用
#define PRINTS(FORMAT,VALUE) printf("The value of "#VALUE" is "FORMAT"\n",VALUE)//这种技巧使用预处理将一个宏参数转换为一个字符串
//#argument这种结构被预处理翻译为"argument"
#define ADD_TO_SUM(sum_number,value) sum ## sum_number += value//##结构则执行不同的任务
//它把位于它两边的符号连接成一个符号,作为用途之一,它允许宏定义从分离的文本片段创建标识符

int main(int argc, const char * argv[]) {
    
    int x = 2;
    PRINT("%d", x + 3);
    PRINTS("%d", x + 3);
    
    int a, b;
    int sum4 = 10;
    int sum5=0;
    a = ADD_TO_SUM(4, 100);//将值100加到变量sum4
    b = ADD_TO_SUM(5, 25);//将值25加到变量sum5
    printf("x=%d\n", a);
    printf("y=%d\n", b);
    
    
    return 0;
}

//在程序中扩展#define定义符号和宏时,需要涉及几个步骤:
//1.在调用宏时,首先对参数进行检查,看看是否包含了任何由#define定义的符号,如果是,它们首先被替换
//2.替换文本随后被插入到程序原来文本的位置,对于宏,参数名被它们的值所替代
//3.最后,再次对结果文本进行扫描,看看是否包含了任何由#define定义的符号,如果是,重复上述处理过程
//这样宏参数的#define定义可以包含其他#define定义的符号,但是宏不可以出现递归
//当预处理器搜索#define定义的符号时,字符串常量的内容并不进行检查,你如果想把宏参数插入到字符串常量中,可以使用两种技巧
//首先,邻近的字符串自动连接的特性使我们很容易把一个字符串分成几段,每段实际上都是一个宏参数
