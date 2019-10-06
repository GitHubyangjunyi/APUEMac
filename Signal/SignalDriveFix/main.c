//
//  main.c
//  SignalDriveFix
//
//  Created by 杨俊艺 on 2019/9/22.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

static void init_handler(int s)
{
    write(1, "!", 1);
}

int main(int argc, const char * argv[]) {
    
    int i, j;
    sigset_t set, oldset, saveset;
       
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    signal(SIGINT, init_handler);
    sigprocmask(SIG_UNBLOCK, &set, &saveset);///<--保存进入这个模块之前的外部状态
    sigprocmask(SIG_BLOCK, &set, &oldset);//阻塞中断
    for (j = 0; j < 1000; j++)
    {
        for (i = 0; i < 5; i++)
        {
            write(1, "X", 1);
            sleep(1);
        }
        write(1, "\n", 1);
        
        //这4条语句相当于sigsuspend(&oldset),但下面的4条语句没有原子化,是不可靠的
//        sigset_t tmpset;
//        sigprocmask(SIG_SETMASK, &oldset, &tmpset);//恢复信号,在调用sigprocmask后如果有任何未决的,不再阻塞的信号,则在sigprocmask返回前至少将其中之一递送给该进程
                        ///<--时间窗口竞争条件,在解除阻塞和pausae之间发生了信号,就会使得信号永远丢失,pause永远阻塞,这是不可靠信号的一个问题,为了纠正时间窗口,需要在一个原子操作中先恢复信号屏蔽字,然后进入pause休眠,这种功能是由sigsuspend提供的
//        pause();
//        sigprocmask(SIG_SETMASK, &tmpset, NULL);//唤醒了再阻塞中断
        //
        sigsuspend(&oldset);//为了实现对一个信号解除阻塞,然后pause以等待以前被阻塞的信号发生这一目的
        //进程的信号屏蔽字由参数指定,在捕捉到一个信号或发生了一个会终止该进程的信号之前,进程被挂起
        //如果捕捉到一个信号并且从该信号处理程序返回,则sigsuspend返回,并且该进程的信号屏蔽字设置为调用sigsuspend之前的值
        //sigsuspend函数没有成功返回值,如果返回调用者总是返回-1,并将errno设置为EINTR,表示一个被中断的系统调用
        //这个sigsuspend将会解除对信号的阻塞并进入休眠,然后捕捉到一个信号后而且从该信号处理函数返回,则sigsuspend返回,并且该进程的信号屏蔽字设置为调用sigsuspend之前的值,也就是再次屏蔽信号
    }
    
    sigprocmask(SIG_SETMASK, &saveset, NULL);///<--恢复进入这个模块之前的外部状态
    
    return 0;
}

//应该使用终端运行./SignalDriveFix
//要求效果
//先打印一行,到第二行打印时停住,等待用户信号,用户发送了信号才会驱动程序继续
//yangjunyideMac-mini:Debug yangjunyi$ ./SignalDriveFix
//XXXXX
//^C!XXXXX
//^C!XX^CXXX
//!XXXXX
//^C!XXX^C^CXX
//!XXXXX
//看完接着看SignalDriveFix或者临界区保护
