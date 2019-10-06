//
//  main.c
//  ZombieProcess
//
//  Created by 杨俊艺 on 2019/9/15.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
    
    //改版的代码
    pid_t pid;
    printf("parent pid = %d\n", getpid());

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        if ((pid = fork()) < 0)
            printf("fork error\n");
        else if (pid > 0){
            printf("first child pid = %d\n", getpid());
            printf("first child, parent pid = %ld\n", (long)getppid());
            exit(0);
        }

        //sleep(2);//这一句注释掉结果将发生变化
        while (getppid() != 1) {//轮询父进程是否终止,导致自己被init进程收养,init进程id是1
            sleep(1);
        }
        printf("second child pid = %d\n", getpid());
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }
    if (waitpid(pid, NULL, 0) != pid) {
        printf("waitpid error\n");
    }

    exit(0);
    
    
    
    
    
    //原版代码
//    pid_t pid;
//
//    if ((pid = fork()) < 0) {
//        printf("fork error\n");
//    } else if (pid == 0) {
//        if ((pid = fork()) < 0)
//            printf("fork error\n");
//        else if (pid > 0){
//            exit(0);
//        }
//
//        sleep(2);
//        printf("second child, parent pid = %ld\n", (long)getppid());
//        exit(0);
//    }
//    if (waitpid(pid, NULL, 0) != pid) {
//        printf("waitpid error\n");
//    }
//
//    exit(0);
}

//如果一个进程fork一个子进程但不要它等待子进程终止,也不希望子进程处于僵死状态直到父进程终止,实现这一要求需要调用fork两次
//./a.out(使用终端运行,而不是在Xcode中运行)
//second child, parent pid = 1
//第二个子进程调用sleep保证在打印父进程id时第一个子进程已经终止
//在fork之后父进程和子进程都可以继续执行,并且无法预知哪一个先执行,在fork之后如果不使第二个子进程休眠,那么它可能比其父进程先执行
//于是打印的父进程id将会是创建它的父进程而不是init进程1
//
//我也是服了,在Xcode控制台运行结果与命令行运行不一致
//我也是服了,在Xcode控制台运行结果与命令行运行不一致
//在终端中运行改版的代码
//parent pid = 2013
//first child pid = 2014
//first child, parent pid = 2013
//second child pid = 2015
//second child, parent pid = 1
