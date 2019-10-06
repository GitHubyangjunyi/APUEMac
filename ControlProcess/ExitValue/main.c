//
//  main.c
//  ExitValue
//
//  Created by 杨俊艺 on 2019/9/15.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void pr_exit(int status);

int main(int argc, const char * argv[]) {
    
    pid_t pid;
    int status;
    
    if ((pid = fork()) < 0)
        fprintf(stderr, "fork error\n");
    else if (pid == 0)
        exit(7);//退出参数
    
    if (wait(&status) != pid) {//调用wait阻塞父进程
        fprintf(stderr, "wait error\n");
    }
    pr_exit(status);//父进程获得子进程的退出状态7
    
    
    if ((pid = fork()) < 0)
        fprintf(stderr, "fork error\n");
    else if (pid == 0)
        abort();//abort会结束子进程并发送SIGABORT信号唤醒父进程
    
    if (wait(&status) != pid)
        fprintf(stderr, "wait error\n");
    pr_exit(status);
    
    
    if ((pid = fork()) < 0)
        fprintf(stderr, "fork error\n");
    else if (pid == 0)
        status /= 0;
    
    if (wait(&status) != pid)
        fprintf(stderr, "wait error\n");
    pr_exit(status);
    
    
    exit(0);
}

void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
        WCOREDUMP(status) ? "(core file generated)" : "");
#else
        "");
#endif
    else if (WIFSTOPPED(status))
        printf("child sopped, signal number = %d\n", WSTOPSIG(status));
}

//我也是服了,在Xcode控制台运行结果与命令行运行不一致
//我也是服了,在Xcode控制台运行结果与命令行运行不一致
//从终端运行结果为7 6 8
//从Xcode运行结果为0 7 7
