//
//  main.c
//  Processcontrol
//
//  Created by 杨俊艺 on 2019/9/5.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 4096

int main(int argc, const char * argv[]) {
    
    char buf[MAXLINE];
    pid_t pid = 0;
    int status;
    
    printf("%%");
    while(fgets(buf, MAXLINE, stdin) != NULL){//fgets函数从标准输入读取一行,当键入文件结束符Ctrl+D作为行的第一个字符时,返回null指针,于是循环停止,程序终止
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;//格式化参数传递给execlp,execlp函数要求的参数是以null结束而不是换行
        
        if((pid=fork()) < 0){//调用fork创建一个新进程,新进程是调用进程的一个副本,调用进程为父进程,fork对父进程返回新的子进程的ID(一个非负整数),对子进程返回0
            printf("fork error");//因为fork创建一个新进程,所以说它被调用一次(由父进程),但返回两次(分别在父进程和子进程中)
        }
        else if(pid == 0){//在子进程中调用execlp执行从标准输入读入的命令,这就用新的程序文件替换了子进程原先执行的程序文件
            execlp(buf, buf,(char *)0);//fork和跟随其后的exec两者的组合就是某些操作系统所称的产生(spawn)一个新进程,在Unix系统中这两部分分离成独立的两个函数
            printf("couldn't execute: %s", buf);
            exit(127);
        }
        
        if ((pid= waitpid(pid, &status, 0)) < 0){//子进程调用execlp执行新的程序文件,而父进程希望等待子进程终结,这是通过调用waitpid实现的
            printf("waitpid error");//其参数指定要等待的进程,pid是子进程ID,waitpid函数返回子进程的终止状态status
        }
        printf("%%");
    }
    
    
    exit(0);
}

//应该从终端运行
//该程序的限制是不能向所执行的命令传递参数,为了传递参数,先要分析输入行,然后用某种约定把参数分开(可能使用空格或制表符),再将分隔后的各个参数传递给execlp函数
//通常一个进程只有一个控制线程thread--某一时刻执行的一组机器指令
//一个进程内的所有线程共享同一地址空间/文件描述符/栈以及进程相关的属性,因为它们能访问同一存储区,所以各个线程在访问共享资源时需要采取同步措施以避免不一致性
//与进程相同,线程也用ID标识,但是线程ID只在它所属的进程内起作用,一个进程中的线程ID在别的进程中没有意义,当一进程对某个特定线程进行处理时,可以使用该线程的ID来引用
//线程模型是在进程模型建立很久之后才被引入到Unix系统中的
