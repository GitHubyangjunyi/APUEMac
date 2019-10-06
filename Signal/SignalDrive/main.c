//
//  main.c
//  SignalDrive
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
    //sleep(1);
    sigprocmask(SIG_UNBLOCK, &set, &saveset);///<--保存进入这个模块之前的外部状态
    for (j = 0; j < 1000; j++)
    {
        //前面sleep为了测试在进入这里阻塞信号之前能不能响应,答案是可以响应中断信号,一般程序运行,用户中断之前程序已经执行到内层for中了,这个测试可以先忽略
        sigprocmask(SIG_BLOCK, &set, &oldset);//阻塞信号
        for (i = 0; i < 5; i++)
        {
            write(1, "X", 1);
            sleep(1);
        }
        write(1, "\n", 1);
        
        sigprocmask(SIG_SETMASK, &oldset, NULL);//恢复信号,在调用sigprocmask后如果有任何未决的,不再阻塞的信号,则在sigprocmask返回前至少将其中之一递送给该进程
                                    ///<--时间窗口竞争条件,在解除阻塞和pausae之间发生了信号,就会使得信号永远丢失,pause永远阻塞,上下两句不原子导致的问题看下面
        pause();
    }
    
    sigprocmask(SIG_SETMASK, &saveset, NULL);///<--恢复进入这个模块之前的外部状态
    
    return 0;
}

//应该使用终端运行./SignalDrive
//要求效果
//先打印一行,到第二行打印时停住,等待用户信号,用户发送了信号才会驱动程序继续
//程序存在的问题
//yangjunyideMac-mini:Debug yangjunyi$ ./SignalDrive
//XXXXX
//^C!XXXXX
//^C!XX^CXXX  中途发生了信号打断阻塞的系统调用,但是信号被阻塞了不响应,但是pending还是为1,一旦恢复了信号但未执行pause的窗口中被内核挂起并重新调度运行,响应一次信号(下一行的!)
//!^C!XXXXX      响应完信号pause休眠了,再一次中断才会令程序继续执行
//^C!XX^CX^CXX    中途插入多个信号
//!           只响应一个
