//
//  main.c
//  Printd
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void printd(int n);

int main(int argc, const char * argv[]) {
    
    
    printd(-2147483648);//无法处理最大的负数
    printf("\n");
    printd(-2147483647);
    printf("\n");
    printd(2147483647);
    printf("\n");
    printd(123);
    printf("\n");
    printd(10);
    printf("\n");
    
    
    return 0;
}

void printd(int n)//无法处理最大的负数
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

//打印十进制数
//在C语言中,函数可以直接或间接调用自身,即可以递归调用
//将一个数作为一个字符串打印的情况,数字是以反序生成的,低位数字先于高位数字生成,必须以相反的次序打印
//解决办法有两种,一种是将生成的各个数字依次存储到一个数组中,然后以相反的次序打印,另一种是递归
//函数printd首先调用自身打印前面的高位数字,然后在打印后面的数字,这里的printd不能处理最大的负数
//函数递归调用自身时,每次调用都会得到一个与以前的自动变量集合不同的新的自动变量集合
//在调用printd(123)时,第一次调用的参数n=123,它把12传递给printd的第二次调用,后者又把1传递给printd的第三次调用
//第三次调用printd时将打印1,然后再返回到第二次调用,从第三次调用返回后的第二次调用同样也将先打印2,然后再返回到第一次调用
//返回到第一次调用时将打印3,随之结束函数执行
//另一个好的例子时快速排序QuickSort,位于Sort项目文件夹内
