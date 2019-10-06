//
//  main.c
//  SigSetFunctionImplementmentaton
//
//  Created by 杨俊艺 on 2019/9/21.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

#define SIGBADT(signo) ((signo) <= 0 || (signo) >= NSIG)

int sigaddsetx(sigset_t *set, int signo)
{
    if (SIGBADT(<#signo#>)) {
        errno = EINVAL;
        return -1;
    }
    *set |= 1 << (signo - 1);
    return 0;
}

int sigdelsetx(sigset_t *set, int signo)
{
    if (SIGBADT(<#signo#>)) {
        errno = EINVAL;
        return -1;
    }
    *set &= ~(1 << (signo - 1));
    return 0;
}

int sigismemberx(const sigset_t *set, int signo)
{
    if (SIGBADT(<#signo#>)) {
        errno = EINVAL;
        return -1;
    }
    return ((*set & (1 << (signo - 1))) != 0);
}

int main(int argc, const char * argv[]) {
    
    
    return 0;
}
