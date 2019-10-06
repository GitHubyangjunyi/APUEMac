//
//  main.c
//  CriticalZoneProtection
//
//  Created by 杨俊艺 on 2019/9/22.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void
pr_mask(const char *str)
{
    sigset_t    sigset;
    int            errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        //err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");

        printf("\n");
    }

    errno = errno_save;
}

int main(int argc, const char * argv[]) {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
