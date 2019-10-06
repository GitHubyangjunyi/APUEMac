//
//  main.c
//  Sigpending
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

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        perror("can't reset SIGQUIT");
    }
}

int main(int argc, const char * argv[]) {
    
    sigset_t newmask, oldmask, pendmask;
    
    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        perror("can't catch SIGQUIT");
    }
    
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("SIG_BLOCK error");
    }
    
    sleep(5);
    
    if (sigpending(&pendmask) < 0) {
        perror("sigpending error");
    }
    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\nSIGQUIT pending\n");
    }
    
    
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {//在休眠期间如果产生了退出信号,此时信号是未决的,但不再阻塞,所以在sigprocmask返回之前被递送到调用进程,所以信号处理函数中printf先执行,然后在执行后面的unblocked
        perror("SIG_SETMASK error");
    }
    
    printf("\nSIGQUIT unblocked\n");
    
    
    
    sleep(5);
    exit(0);
}

//运行结果
//yangjunyideMac-mini:Debug yangjunyi$ ./Sigpending
//^\                5秒之内
//SIGQUIT pending
//caught SIGQUIT
//
//SIGQUIT unblocked
//yangjunyideMac-mini:Debug yangjunyi$ ./Sigpending
//^\
//SIGQUIT pending
//caught SIGQUIT
//
//SIGQUIT unblocked
//^\Quit: 3
//yangjunyideMac-mini:Debug yangjunyi$ ./Sigpending
//^\^\^\^\^\^\^\^\^\^\5秒之内
//SIGQUIT pending
//caught SIGQUIT
//
//SIGQUIT unblocked
//yangjunyideMac-mini:Debug yangjunyi$
