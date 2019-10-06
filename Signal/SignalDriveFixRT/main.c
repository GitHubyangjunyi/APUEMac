//
//  main.c
//  SignalDriveFixRT
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

#define MYRTSIG  (SIGRTMIN + 6)

static void my_handler(int s)
{
    write(1, "!", 1);
}

int main(int argc, const char * argv[]) {
    
    int i, j;
    sigset_t set, oldset, saveset;
       
    sigemptyset(&set);
    
//    sigaddset(&set, MYRTSIG);
//    signal(MYRTSIG, my_handler);
    //将下面的两句替换上面的两句,在Linux下运行
    sigaddset(&set, SIGINT);
    signal(SIGINT, my_handler);
    
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
        
        //这4条语句相当于sigsuspend(&oldset),但下面的4条语句没有原子化
//        sigset_t tmpset;
//        sigprocmask(SIG_SETMASK, &oldset, &tmpset);//恢复中断
                        ///<--时间窗口竞争条件,在解除阻塞和pausae之间发生了信号,就会使得信号永远丢失,pause永远阻塞
//        pause();
//        sigprocmask(SIG_SETMASK, &tmpset, NULL);//唤醒了再阻塞中断
        //
        sigsuspend(&oldset);
    }
    
    sigprocmask(SIG_SETMASK, &saveset, NULL);///<--恢复进入这个模块之前的外部状态
    
    return 0;
}

//应该使用终端运行./SignalDrive
//另开一个终端发送信号kill -40 pid
//要求效果
//先打印一行,到第二行打印时停住,等待用户信号,用户发送了信号才会驱动程序继续
//yangjunyideMac-mini:Debug yangjunyi$ ./SignalDriveFix
//XXXXX
//^C!XXXXX
//^C!XX^CXXX
//!XXXXX
//^C!XXX^C^CXX
//!XXXXX
