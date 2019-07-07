//
//  main.c
//  GNUCMacroExtendFix
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

//从这里开始看
#define A(x) a##x
//宏连接符##的主要作用就是连接两个字符串,在预处理阶段对宏展开时会将##两边的字符合并,并删除##这两个字符
//这个宏的功能就是连接字符a和x,在程序中A(1)展开后就是a1,A()展开后就是a,我们使用printf()函数可以直接打印变量a1/a的值
//因为宏展开后就相当于使用int关键字定义了两个整型变量a1和a,上面的程序可以编译通过
//知道了宏连接符##的使用方法,我们接下来就可以就对LOGMACROERROR宏做一些修改
#define    LOGMACROERROR(fmt, ...) printf(fmt, __VA_ARGS__)
#define LOGMACROFIX(fmt,...) printf(fmt, ##__VA_ARGS__)

//我们在标识符__VA_ARGS__前面加上宏连接符##,这样做的好处是当变参列表非空时,##的作用是连接fmt和变参列表,各个参数之间用逗号隔开,宏可以正常使用
//当变参列表为空时,##还有一个特殊的用处,它会将固定参数fmt后面的逗号删除掉,这样宏也就可以正常使用了

int main(int argc, const char * argv[]) {
    
    int A(1) = 2;//int a1 = 2;
    int A() = 3; //int a=3;
    printf("%d %d\n", a1, a);//    2  3
    
    
    LOGMACROERROR("LOGMACROERROR:    hello\n");//Linux环境下使用GCC编译将出现语法错误,目前环境下并不会出现错误???
    LOGMACROFIX("LOGMACROFIX:    hello\n");//Linux环境下使用GCC编译正常运行,目前环境下也正常运行

    
    return 0;
}
