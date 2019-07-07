//
//  main.c
//  BlockStructurePro
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int global_init_var = 84;//外部可以通过extern声明引用
int global_uninit_var = 111;

extern int static_var2;

static const int static_int = 12;//静态全局变量不可变->常量?

extern int var2;
extern int var3;
extern const int var4;//引用过来是加上const限定防止意外修改,权限设置?
extern const int var5;

extern void func2(void);
extern void funcadd(void);

int main(int argc, const char * argv[]) {
    
    
    //static_var2++;//异常
    printf("main: extern static_var2 = %d\n", static_var2);//1
    printf("main: static_int = %d\n", static_int);//12
    
    func2();
    printf("main: static_int = %d\n", static_int);//12
    func2();
    
    printf("main: extern int var2 = %d\n", var2);
    var2++;
    printf("main: extern int var2 = %d\n", var2);
    
    printf("main: extern int var3 = %d\n", var3);
    //var3++;//因为加了const限定不可修改,运行时将出现异常
    printf("main: extern int var3 = %d\n", var3);
    
    printf("main: extern int var4 = %d\n", var4);
    //var4++;//直接报错不可编译
    printf("main: extern int var4 = %d\n", var4);
    
    funcadd();
    printf("funcadd: var5 = %d\n", var5);
    
    
    return 0;
}
