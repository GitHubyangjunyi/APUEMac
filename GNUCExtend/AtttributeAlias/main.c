//
//  main.c
//  AtttributeAlias
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    

    
    
    return 0;
}

//GNU C扩展了一个alias属性用来给函数定义一个别名
//
//void __f(void)
//{
//    printf("__f\n");
//}
//
//void f() __attribute__((alias("__f")));//定义__f()函数的别名为f()
//
//int main(void)
//{
//    f();
//    return 0;
//}
//
//运行结果
//__f
//通过alias属性声明就可以给__f()函数定义一个别名f(),以后我们想调用__f()函数可以直接通过f()调用即可
//
//在Linux内核中你会发现alias有时会和weak属性一起使用,比如有些函数随着内核版本升级函数接口发生了变化
//我们可以通过alias属性给这个旧接口名字做下封装,起一个新接口的名字
////f.c
//
//void __f(void)
//{
//    printf("__f()\n");
//}
//
//void f() __attribute__((weak,alias("__f")));//定义f()函数作为__f()函数的别名,并且f()为弱符号
//
////main.c
//
//void __attribute__((weak)) f(void);//定义f()为弱符号
//
//void f(void)//这个存在则运行这个,如果这个不存在,则f()已经定义为弱符号,main函数就会调用原来的__f()函数且不引起错误
//{
//    printf("f()\n");
//}
//
//int main(void)
//{
//    f();
//    return 0;
//}
