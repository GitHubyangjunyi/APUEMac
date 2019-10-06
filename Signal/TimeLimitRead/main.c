//
//  main.c
//  TimeLimitRead
//
//  Created by 杨俊艺 on 2019/9/21.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

static void sig_alarm(int signo)
{
    
}

int main(int argc, const char * argv[]) {
    
    int n;
    char line[4096];
    
    if (signal(SIGALRM, sig_alarm) == SIG_ERR) {
        perror("signal(SIGALRM) error");
    }
    
    alarm(10);
            ///<----竞争窗口
    if ((n = read(STDIN_FILENO, line, 4096)) < 0) {
        perror("read error");
    }
    
    alarm(0);
    
    write(STDIN_FILENO, line, n);
    
    
    
    exit(0);
}

//除了用来实现sleep外,alarm还常常用来对可能阻塞的操作设置时间上限值
//例如程序中有个读取低速设备的可能阻塞的操作,我们希望在一定时间后能停止执行
//这个程序从标准输入读取一行并写到标准输出
//两个问题
//在第一次调用alarm和read之间有一个竞争条件,如果内核在这两个调用之间令进程阻塞,不能占用处理器运行,而其时间又超过定时器时间
//则read可能永远阻塞,大多数类型的系统在使用这种类型的操作时都会设定较长的时间,但是无论如何这是一个竞争条件
//如果系统是自动重启动的,当从SIGALRM信号处理程序返回时,read并不被中断,这种情况下设置时间限制没有作用
