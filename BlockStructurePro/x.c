//
//  x.c
//  BlockStructurePro
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include "x.h"

int const static_var2 = 1;//不能添加static,否则main引用不到

static const int static_int = 123456;//static限定在当前文件内且不可变
//const int static_int = 123456;//上面语句可以改成这一句
//extern const int static_int = 123456;//上面语句可以改成这一句???extern相当于无效???
//extern const int static_int;//但是不能改成这样,因为别的文件static限定了
//extern工作原理:先会去当前文件下查找有没有对应全局变量,如果没有才会去其他文件查找
int var2 = 222;

int const var3 = 333;

int var4 = 444;

int var5 = 555;

void func2(void)
{
    
    printf("func2: static const static_int = %d\n", static_int);//123456
    
    {
        static int static_int = 666;//只在这个块里改变
        static_int++;
        printf("func2: static int func2_static_int = %d\n", static_int);//666系列
    }
    printf("func2: static int func2_static_int = %d\n", static_int);//123456
    
    var4++;
}
