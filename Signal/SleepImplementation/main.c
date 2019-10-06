//
//  main.c
//  SleepImplementation
//
//  Created by 杨俊艺 on 2019/9/19.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

//从这里开始看sleep函数实现
static void sig_alarm(int signo)
{
    
}

unsigned int sleep1(unsigned int seconds)//最初版本的sleep实现
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR) {
        return seconds;
    }
    alarm(seconds); //设置定时器开始
                    ///<--竞争条件
    pause();        //只有执行了一个信号处理函数并从其返回,pause才会返回,这种情况下啊pause返回-1并设置errno为EINTR,一旦信号触发并处理完毕,pause失效
    return alarm(0);//取消定时器并返回剩余时间,因为alarm参数为零,如果有以前尚未超时的定时器,则alarm(0)将取消定时器并返回剩余时间
}
//sleep1存在的问题
//1如果在调用sleep1执之前调用者已经设置了闹钟,则它被sleep1中的第一次alarm擦除
//更正方法:
//检查第一次调用alarm的返回值,如果小于本次调用alarm的值,则只应该等到原来的闹钟超时
//如果晚于本次的设置值,则在sleep1函数返回之前重置此闹钟使其在之前闹钟的设定时间再次发生超时
//2.该程序中修改了对SIGALRM的配置如果编写了一个函数供其他函数调用,则在该函数被调用时先要保存原来的配置,在该函数返回之前恢复配置
//更正方法:
//保存signal的返回值,在返回前还原
//3.在第一次调用alarm和pause之间有个竞争条件,在一个繁忙的系统中可能alarm在调用pause之前超时,并调用了信号处理函数,在调用pause后如果没有捕捉到其他信号,调用者将被永久挂起
//更正方法:
//使用setjmp或者使用sigprocmask和sgsuspend
//

//SVR2中的sleep实现使用了setjmp和longjmp以避免第三个问题,下面的sleepx是简化版的sleep,并未处理前两个问题
static jmp_buf env_alarm;
static void sig_alarmx(int signo)
{
    longjmp(env_alarm, 1);
}

unsigned int sleepx(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alarmx) == SIG_ERR) {
        return seconds;
    }
    if (setjmp(env_alarm) == 0) {
        alarm(seconds);
                ///<--竞争条件,但是使用了setjmp,无论pause有没有执行,sleepx函数也会返回
        pause();
    }
    return alarm(0);
}
//但是sleepx函数有另外一个难以察觉的问题,涉及到与其他信号的交互,如果SIGALRM中断了其他某个信号处理程序,则调用longjmp会提早结束该信号处理函数
//下面就是示例,SIGINT处理函数中有for循环,在某个系统上执行时间超过5秒,也就是大于sleepx的参数值
//整形变量k带有volatile阻止编译器优化循环语句

static void sig_int(int signo)
{
    int i, j;
    volatile int k = 0;
    
    printf("\nsig_int starting\n");
    for (i = 0; i < 300000; i++) {
        for (j = 0; j < 40000; j++) {
            k += i * j;
        }
    }
    printf("sig_int finished\n");
}

int main(int argc, const char * argv[]) {
    
    unsigned int unslept;
    
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("signal(SIGINT) error!");
    }
    unslept = sleepx(5);
    
    //定时器已经设置,然后按下中断键,进入中断处理函数,中断处理函数将操作超过5秒钟
    
    printf("sleepx return: %u\n", unslept);
    
    
    exit(0);
}
//yangjunyideMac-mini:Debug yangjunyi$ ./SleepImplementation
//^C
//sig_int starting
//sleepx return: 0
//sleepx函数所引起的longjmp使得另一个信号处理程序sig_int提早终止,即使它未完成
//如果将SVR2中的sleep函数与其他信号处理函数一起使用就可能碰到此种情况
//
//yangjunyideMac-mini:Debug yangjunyi$ ./SleepImplementation
//^C
//sig_int starting
//sig_int finished
//sleepx return: 2
//
//
//
//yangjunyideMac-mini:Debug yangjunyi$ ./SleepImplementation
//sleepx return: 0
