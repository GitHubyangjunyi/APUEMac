//
//  main.c
//  GNUCMacroExtendPre
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

//从这里开始看
//在前面我们学会了变参函数的定义和使用,基本套路就是使用va_list/va_start/va_end等宏去解析那些可变参数列表
//我们找到这些参数的存储地址后就可以对这些参数进行处理了,要么自己动手处理,要么继续调用其它函数来处理
void print_num(int count, ...)//在Linux下注释此函数
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        printf("*args: %d\n", *(int *)args);
        args += 4;
    }
}
void
//__attribute__((format(printf, 1, 2)))//在Linux下有没有这行似乎没有影响???
LOG(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
//GNU C觉得这样不过瘾再来个猛锤,干脆宏定义也支持变参吧!其实C99标准已经支持了这个特性,但其它的编译器对C99标准的支持不是很好
//只有GNU C支持这个功能,所以也把这个可变参数宏看作是GNU C的一个语法扩展
//上面的LOG函数,如果我们想使用一个变参宏实现,就可以直接这样定义
#define LOGMACRO(fmt, ...) printf(fmt, __VA_ARGS__)

#define DEBUG(...) printf(__VA_ARGS__)


//变参宏的实现形式其实跟变参函数差不多:用...表示变参列表,变参列表由不确定的参数组成,各个参数之间用逗号隔开
//可变参数宏使用C99标准新增加的一个__VA_ARGS__预定义标识符来表示前面的变参列表,而不是像变参函数一样使用va_list/va_start/va_end这些宏去解析变参列表
//预处理器在将宏展开时会用变参列表替换掉宏定义中的所有__VA_ARGS__标识符
//使用宏定义实现一个变参打印功能你会发现,它的实现甚至比变参函数还方便!内核中的很多打印宏经常使用可变参数宏来实现,宏定义一般为下面这个格式
#define    LOGMACROERROR(fmt, ...) printf(fmt, __VA_ARGS__)

//在这个宏定义中有一个固定参数,通常为一个格式字符串,后面的变参用来打印各种格式的数据,跟前面的格式字符串相匹配
//这种定义方式有一个漏洞,即当变参为空时,宏展开时就会产生一个语法错误导致编译不过,这是因为我们只给LOGMACROERROR宏传递了一个参数
//而变参为空,当宏展开后就变成下面这个样子
//    LOGMACROERROR("hello\n", );
//宏展开后在第一个字符串参数的后面还有一个逗号,所以就产生了一个语法错误,我们需要继续对LOGMACROERROR进行改进,使用宏连接符##来避免这个语法错误

int main(int argc, const char * argv[]) {
    
    print_num(5, 1, 2, 3, 4, 5); //在Linux下注释此函数调用
    print_num(9999);
    LOG("LOG:    Hello! I'm %s\n", "GitHubyangjunyi");
    
    LOGMACRO("LOGMACRO:    Hello! I'm %s\n", "GitHubyangjunyi");
    
    DEBUG("DEBUG:    Hello! I'm %s\n", "GitHubyangjunyi");
    
    LOGMACROERROR("LOGMACROERROR:    hello\n");//Linux环境下使用GCC编译将出现语法错误,目前环境下并不会出现错误???
    
    
    return 0;
}
