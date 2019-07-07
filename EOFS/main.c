//
//  main.c
//  EOFS
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void EOFReturnValue();
void EOFValue();
void EOFTest();

int main(int argc, const char * argv[]) {
   

    EOFReturnValue();
    EOFValue();
    EOFTest();
    
    
    return 0;
}

void EOFReturnValue()//测试当没有输入时getchar()的返回值,直接回车返回10,Ctrl+Z返回-1
{
    int GETCHAREnpty = getchar();
    printf("%d\n", GETCHAREnpty);
}

void EOFValue()//测试EOF的值
{
    printf("EOF is %d\n", EOF);
}

void EOFTest()//验证getchar()!=EOF取值是0还是1
{
    int c;
    while (c=getchar()!=EOF)
    {
        printf("%d\n", c);//行末的回车或Ctrl+Z也算一个字符
    }
    printf("%d - at EOF\n", c);
}

//注意字符流模型
//使用符号常量可以确保不依赖于其对应的任何特定数值,增加可移植性
