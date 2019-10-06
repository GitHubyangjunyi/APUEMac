//
//  main.c
//  SignalSIGUSR
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_usr(int);

int main(int argc, const char * argv[]) {
    
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR1");
    }
    
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR2");
    }
    
    for (; ; ) {
        pause();
    }
}

static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("receved SIGUSR1");
    }
    else if (signo == SIGUSR2)
    {
        printf("receved SIGUSR2");
    }
    else
    {
        printf("received signal %d\n", signo);
    }
    
}
