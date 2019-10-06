//
//  main.c
//  Processsignal
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

static void sig_int(int signo); //信号捕捉函数

int main(int argc, const char * argv[]) {

    char buf[MAXLINE];
    pid_t pid = 0;
    int status;
    //与processcontrol相比增加的内容
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("signal error");
    }
    //与processcontrol相比增加的内容
    
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

//与processcontrol相比增加的内容
void sig_int(int signo)
{
    printf("interrupt\n%%");
}
//与processcontrol相比增加的内容

//应该从终端运行
//该程序的限制是不能向所执行的命令传递参数,为了传递参数,先要分析输入行,然后用某种约定把参数分开(可能使用空格或制表符),再将分隔后的各个参数传递给execlp函数
//通常一个进程只有一个控制线程thread--某一时刻执行的一组机器指令
//一个进程内的所有线程共享同一地址空间/文件描述符/栈以及进程相关的属性,因为它们能访问同一存储区,所以各个线程在访问共享资源时需要采取同步措施以避免不一致性
//与进程相同,线程也用ID标识,但是线程ID只在它所属的进程内起作用,一个进程中的线程ID在别的进程中没有意义,当一进程对某个特定线程进行处理时,可以使用该线程的ID来引用
//线程模型是在进程模型建立很久之后才被引入到Unix系统中的
//
//信号用于通知进程发生了什么事情,例如,若某一进程执行除法操作,除数为0,则将名为SIGFPE的浮点异常信号发送给该进程,进程有以下三种处理信号的方式
//1.忽略信号,有些信号表示硬件异常,比如除0或者访问进程地址空间以外的存储单元,因为后果不确定,所以不推荐使用这种方式
//2.按系统默认方式处理,对于除数0,系统默认终止该进程
//3.提供一个函数,信号发生时调用该函数,则被称为捕捉该信号,通过提供自编写的函数我们就可以知道什么时候产生了信号,并以期望的方式处理
//终端键盘上有两种产生信号的方法,分别称为中断键Delte或Ctrl+C和退出键Ctrl+\,它们被用于中断当前运行的进程
//另一种产生信号的方式是调用kill函数,在一个进程中调用此函数就可以向另一个进程发送一个信号,当然有些限制,当向一个进程发送信号时,我们必须是那个进程的所有者或者是超级用户
//回忆下基本的shell实例,如果调用此程序,然后按下中断键,则执行此进程的程序终止,产生这种后果的原因是对于此信号的系统默认动作是终止进程,该进程没有告诉系统内核如何处理此信号
//所以系统按默认方式终止该进程,为了能捕捉此信号,程序需要调用signal函数,其中指定了当产生SIGINT信号时要调用的函数的名字,函数名为sig_int
