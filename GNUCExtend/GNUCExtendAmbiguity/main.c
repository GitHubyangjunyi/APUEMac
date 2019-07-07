//
//  main.c
//  GNUCExtendAmbiguity
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

#define DEBUG() printf("hello ");printf("else\n");

#define DEBUGFIX()\
do {\
    printf("hello ");printf("else\n");\
}while (0)

int main(int argc, const char * argv[]) {
    
    {
        if (1)
            printf("hello if\n");
        else
            DEBUG();
    }
    printf("FIX\n");
    {
        if (1)
            printf("hello if\n");
        else
            DEBUGFIX();
    }
    
    
    
    return 0;
}

//do { ... } while(0)结构这看起来貌似有点多余,有它没它我们的宏都可以工作,反正都是执行一次
//为什么要用这种看似画蛇添足的循环结构呢?道理很简单,这样定义就是为了防止宏在条件,选择等分支结构的语句中展开后,产生宏歧义
//这个程序理论情况下else分支是执行不到的,但通过运行结果可以看到也执行了else分支的一部分代码,这是因为我们定义的宏由多条语句组成
//直接展开后就变成了下面这样
//int main(void)
//{
//    if (1)
//        printf("hello if\n");
//    else
//        printf("hello ");
//        printf("else\n");
//    return 0;
//}
//
//多条语句在宏调用处直接展开就破坏了程序原来的if-else分支结构,导致程序逻辑发生变化,所以才会看到else分支的非正常打印
//而采用do { ... } while(0)这种结构可以将我们宏定义中的复合语句包起来,宏展开后就是一个代码块,就避免了这种逻辑错误
