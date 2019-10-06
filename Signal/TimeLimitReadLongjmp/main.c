//
//  main.c
//  TimeLimitReadLongjmp
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

static jmp_buf env_alarm;

static void sig_alarm(int signo)
{
    longjmp(env_alarm, 1);
}

int main(int argc, const char * argv[]) {
    
    int n;
    char line[4096];
    
    if (signal(SIGALRM, sig_alarm) == SIG_ERR) {
        perror("signal(SIGALRM) error");
    }
    
    //无论慢速的系统调用是否被中断
    //不管系统是否重新启动被中断的系统调用,程序都会预期工作,但是还是存在与其他信号交互的问题,可以选择使用select或者epoll函数
    if (setjmp(env_alarm) != 0) {
        perror("setjmp(env_alarm) error");
        exit(-1);
    }
    //
    
    alarm(10);
            ///<----竞争窗口
    if ((n = read(STDIN_FILENO, line, 4096)) < 0) {
        perror("read error");
    }
    
    alarm(0);
    
    write(STDIN_FILENO, line, n);
    
    
    
    
    
    
    
    exit(0);
}
