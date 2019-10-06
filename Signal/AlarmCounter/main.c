//
//  main.c
//  AlarmCounter
//
//  Created by 杨俊艺 on 2019/9/19.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

static volatile int loop = 1;

static void alarm_handler(int s)
{
    loop = 0;
}

int main(int argc, const char * argv[])
{
    //在终端运行time ./AlarmCounter
    //使用信号明显比使用时间戳更为精确且占用资源更少
    int64_t count = 0;
    
    signal(SIGALRM, alarm_handler);
    
    alarm(5);
    
    
    while (loop) {//关于GCC优化问题,开启O1级别的优化就会导致程序死循环,因为GCC认为循环体中没有使用到loop,那么loop是一成不变的,循环判断被优化掉
        count++;    //这时候volatile就可以派上用场了
    }
    
    printf("%lld\n", count);
    
    
    //使用时间戳进行时间控制
//    time_t end;
//    int64_t count = 0;
//
//    end = time(NULL) + 5;
//
//    while (time(NULL) <= end) {
//        count++;
//    }
//
//    printf("%lld\n", count);
    
    
    exit(0);
}

//关于GCC优化问题
//删除volatile关键字在进行不同优化级别编译,然后查看while循环的优化情况
//gcc -S main.c
//gcc -S main.c -O1
//如果开启优化将放大结果,在某些平台上甚至可以放大十倍
