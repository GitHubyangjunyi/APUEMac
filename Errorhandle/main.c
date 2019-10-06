//
//  main.c
//  Errorhandle
//
//  Created by 杨俊艺 on 2019/9/5.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno=ENOENT;
    perror(argv[0]);
    
    //将程序名作为参数传递给perror
    //这是Unix惯例,使用这种方法,在程序作为管道的一部分执行时,例如:
    //  prog1 < inputfile | prog2 | prog3 > outputfile
    //就能分清3个程序中的哪一个产生了一条特定的出错信息
    //本书的所有实例基本上都不直接调用strerror和perror,而是使用附录B中的出错函数,使我们只使用一条语句就可以利用ISO C的可变参数表功能处理出错情况
    
    exit(0);
}

//POSIX和ISO C将errno定义为一个符号,它扩展成为一个可以修改的左值,是一个包含出错编号的整数,也可以是一个返回出错编号指针的函数
//以前使用的定义是:
//extern int errno;
//但是在支持线程的环境中,多个线程共享进程地址空间,每个线程都有自己的局部errno以避免一个线程干扰另一个线程,例如linux支持多线程存取errno,将其定义为:
//  extern int *__errno_location(void);
//  #define errno (*__errno_location())
//对于errno应当注意两条规则:
//1.如果例程没有出错,其值不会被清除,因此仅当函数的返回值指明出错时才检验其值
//2.任何函数都不会将errno值设置为0,而且在<errno.h>中定义的所有常量都不为0
//C标准定义了两个函数用来输出错误信息
//  #include <string.h>
//  char *strerror(int errnum);
//strerror函数将errnum(通常就是errno)映射为一个错误信息字符串,并且返回此字符串的指针
//perror函数基于errno的当前值,在标准错误上产生一条错误信息,然后返回
//  #include <stdio.h>
//  void perror(const char *msg);
//首先输出由msg指向的字符串然后是一个冒号,一个空格,接着对应于errno值的出错信息,最后是一个换行符
//至于为什么要用const限定是因为msg参数是一个指针,perror就可以改变msg指向的字符串,使用const限制修改
//而对于strerror,其错误参数是整数类型,并且C是按值传递所有参数,因此即使strerror想修改参数也是没有办法的
//
//出错恢复
//可将<errno.h>中定义的各种出错分为两类:致命错误和非致命错误
//对于致命性错误无法恢复动作,最多能做的就是在用户屏幕上打印一条出错信息或者将一条错误信息写入日志,然后退出
//与资源相关的非致命错误包括:EAGAIN ENFILE ENOBUFS ENOLCK ENOSPC EWOULDBLOCK
//有时候ENOMEM也是非致命错误,当EBUSY指明共享资源正在使用时,也可将它作为非致命错误处理,当EINTR中断一个慢速系统调用时,可将其作为非致命错误处理
//对于资源相关的非致命错误的典型恢复操作是延迟一段时间然后重试,例如假设出错表明一个网络连接不再起作用,就可以在短时间延迟后,尝试重新连接
//一些应用应该使用指数补偿算法,在每次迭代中等待更长时间
