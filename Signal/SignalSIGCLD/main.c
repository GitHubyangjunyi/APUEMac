//
//  main.c
//  SignalSIGCLD
//
//  Created by 杨俊艺 on 2019/9/21.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

void sigchld_handler( int signo ){
    printf("sigchld_handler\n");
    sleep(3);
    return;
}

int main(int argc, const char * argv[]) {
    int i;
    pid_t pid;
    pid_t cpid;
    signal( SIGCHLD, sigchld_handler );
    for( i=0; i<5; i++ ){
        pid = fork();
        if ( pid == 0 ){
            sleep(2);
            exit(0);
        }
        else if ( pid == -1 ){
            perror( "fork" );
            exit(-1);
        }
    }
    printf("before wait\n");
    system( "ps -ef | grep ttt" );
    // while((cpid = waitpid(-1,NULL,0)!=-1)) {
    while ((cpid = wait(NULL)) != -1) {
        printf("wait pid is %d\n", cpid);
        continue;
    }
    printf("after wait\n");
    system( "ps -ef | grep ttt" );
}

//gcc -g -o ttt x.c
//./ttt
//这是一个sig和wait联合处理到例子,通常做法有2种,1是在sig处理函数中调用wait处理
//2是不要sig处理函数单独调用wait处理,但是程序结果让人很意外,为什么当产生SIGCHLD信号时wait阻塞没有被中断而是处理正常
//所有子进程都正确退出没有产生僵尸进程呢,按理说wait阻塞时,当产生SIGCHLD信号应该中断同时返回-1,errorno设为EINTR
