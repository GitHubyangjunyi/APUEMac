//
//  main.c
//  Sigprocmask
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

static void init_handler(int s)
{
    write(1, "!", 1);
}

int main(int argc, const char * argv[]) {
    
    int i, j;
    sigset_t set, oldset, saveset;
    
    sigprocmask(SIG_UNBLOCK, &set, &saveset);///<--保存进入这个模块之前的外部状态
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    signal(SIGINT, init_handler);
    
    for (j = 0; j < 1000; j++)
    {
        sigprocmask(SIG_BLOCK, &set, &oldset);//阻塞信号
        for (i = 0; i < 5; i++)
        {
            write(1, "X", 1);
            sleep(1);
        }
        write(1, "\n", 1);
        sigprocmask(SIG_SETMASK, &oldset, NULL);//恢复信号
    }
    
    sigprocmask(SIG_SETMASK, &saveset, NULL);///<--恢复进入这个模块之前的外部状态
    
    return 0;
}

//应该使用终端运行./Sigprocmask
//由于信号会打断阻塞的系统调用,所以如果程序运行时一直发送Ctrl+C则会加速程序执行
//
//限制在两行之间响应中断信号
//XXXXX
//XX^CXXX
//!XXXXX^C^C
//!X^C^CXXXX
//不会立即响应且是在下一行响应,并且多次中断只会响应一次
