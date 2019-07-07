//
//  main.c
//  GNUCMacroExtendApply
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

//内核中的可变参数宏在内核中主要用于日志打印,一些驱动模块或子系统有时候会定义自己的打印宏,可以支持打印开关/打印格式/优先级控制等
//如在printk.h头文件中我们可以看到pr_debug宏的定义
#if defined(CONFIG_DYNAMIC_DEBUG)
#define pr_debug(fmt, ...) dynamic_pr_debug(fmt, ##__VA_ARGS__)
#elif defined(DEBUG)
#define pr_debug(fmt, ...) printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...) no_printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#endif

#define dynamic_pr_debug(fmt, ...)\
do {\
    DEFINE_DYNAMIC_DEBUG_METADATA(descriptor, fmt);\
    if (unlikely(descriptor.flags & _DPRINTK_FLAGS_PRINT))\
        __dynamic_pr_debug(&descriptor, pr_fmt(fmt), ##__VA_ARGS__);\
}while(0)

//static inline __printf(1, 2)
//int no_printk(const char *fmt, ...)
//{
//    return 0;
//}

#define __printf(a, b)  __attribute__((format(printf, a, b)))

//看到这个宏定义不得不佩服宏的作者,一个小小的宏综合运用各种技巧和知识点,把C语言发挥到极致
//这个宏定义了三个版本,如果我们在编译内核时有动态调试选项,那么这个宏就定义为dynamicprdebug
//如果没有配置动态调试选项那我们还可以通过DEBUG这个宏来控制这个宏的打开和关闭
//no_printk()作为一个内联函数,定义在printk.h头文件中,而且通过format属性声明,指示编译器按照printf标准去做参数格式检查
//有意思的是dynamicprdebug宏定义采用do { ... } while(0)结构这看起来貌似有点多余,有它没它我们的宏都可以工作,反正都是执行一次
//为什么要用这种看似画蛇添足的循环结构呢?道理很简单,这样定义就是为了防止宏在条件,选择等分支结构的语句中展开后,产生宏歧义
//比如我们定义一个宏由两条打印语句构成
//#define DEBUG() printf("hello ");printf("else\n")
//
//int main(void)
//{
//    if (1)
//        printf("hello if\n");
//    else
//        DEBUG();
//    return 0;
//}
//
//理论情况下else分支是执行不到的,但通过运行结果可以看到程序也执行了else分支的一部分代码,这是因为我们定义的宏由多条语句组成,直接展开后就变成了下面这样
//int main(void)
//{
//    if (1)
//        printf("hello if\n");
//    else
//        printf("hello ");
//    printf("else\n");
//    return 0;
//}
//
//多条语句在宏调用处直接展开就破坏了程序原来的if-else分支结构,导致程序逻辑发生变化,所以你才会看到else分支的非正常打印
//而采用do { ... } while(0)这种结构可以将我们宏定义中的复合语句包起来,宏展开后就是一个代码块,就避免了这种逻辑错误


int main(int argc, const char * argv[]) {
    
    
    
    
    
    
    return 0;
}
