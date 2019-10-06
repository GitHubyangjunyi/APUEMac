//
//  main.c
//  Shell2
//
//  Created by 杨俊艺 on 2019/9/17.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int paserargs(char *cmdline);

char *cmdargv[20] = {0};

int main(int argc, const char * argv[])
{
    
    pid_t pid;
    char buf[100];
    int retval;
    printf("XShell#");
    fflush(stdout);
    
    while (1) {
        fgets(buf, 100, stdin);
        buf[strlen(buf) - 1] = '\0';
        
        if ((pid = fork()) < 0) {
            perror("fork:");
            exit(-1);
        }
        else if (pid == 0){
            paserargs(buf);
            execvp(cmdargv[0], cmdargv);
            exit(0);
        }else{
            wait(&retval);//等待子进程结束,避免产生过多僵尸进程
            printf("XShell#");
            fflush(stdout);
        }
        
    }
    
}

int paserargs(char *cmdline)
{
    char *head, *tail;
    int i;
    head = tail = cmdline;
    
    for (; *tail == ' '; tail++)
        ;//定位出第一个有效字符
    
    head = tail;//head指向第一个有效字符
    
    for (i = 0; *tail != '\0'; i++)
    {
        cmdargv[i] = head;
        
        for (; (*tail != ' ') && (*tail != '\0'); tail++)//一直步进到下一个参数前的空白符或者参数全部结束
            ;
        
        if (*tail == '\0')//如果达到字符串尾部,那么进入下一个循环判断,很明显循环判断将会失败,而i在将会加上1
            continue;
        
        *tail++  = '\0';//收尾一个参数
        
        for (; *tail == ' '; tail++)
            ;
        head = tail;//步进到下一个参数
    }
    
    cmdargv[i] = '\0';
    
    return i;
}

//书本坑人,印刷各种错误
//只能使用外部命令,且结束时有bug,不如Shell项目
