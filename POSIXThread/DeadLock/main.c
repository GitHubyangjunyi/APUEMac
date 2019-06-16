//
//  main.c
//  DeadLock
//
//  Created by 杨俊艺 on 2019/6/13.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static const char * const caller[2] = {"mutex_thread", "signal handler"};
static pthread_t mutex_tid;
static pthread_t sleep_tid;
static volatile int signal_handler_exit = 0;

static void hold_mutex(int c)
{
    printf("enter hold_mutex[caller %s]\n", caller[c]);
    pthread_mutex_lock(&mutex);
    while (! signal_handler_exit && c != 1)//这里的循环是为了保证锁不会在信号处理函数退出前被释放掉
    {
        sleep(5);
    }
    pthread_mutex_unlock(&mutex);
    printf("leave hold_mutex[caller %s]\n", caller[c]);
}

static void mutex_thread(void *arg)
{
    hold_mutex(0);
}

static void sleep_thread(void *arg)
{
    sleep(10);
}

static void signal_handler(int signum)
{
    hold_mutex(1);
    signal_handler_exit = 1;
}

int main(int argc, const char * argv[])
{
    signal(SIGUSR1, signal_handler);
    
    pthread_create(&mutex_tid, NULL, mutex_thread, NULL);
    pthread_create(&sleep_tid, NULL, sleep_thread, NULL);
    
    pthread_kill(sleep_tid, SIGUSR1);
    
    pthread_join(mutex_tid, NULL);
    pthread_join(sleep_tid, NULL);
    
    
    return 0;
}

//死锁是因为函数hold_mutex是不可重入函数，其中使用了pthread_mutex信号量，当mutex_thread获得mutex时
//sleep_thread就收到了信号，再次调用就进入了hold_mutex，结果始终无法拿到mutex
//信号处理函数无法返回，正常的程序执行流程也无法继续
