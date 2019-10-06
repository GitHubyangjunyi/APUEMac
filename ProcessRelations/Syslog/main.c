//
//  main.c
//  Syslog
//
//  Created by 杨俊艺 on 2019/9/23.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FNAME   "daemon.txt"

static int daemonize(void)
{
    int fd;
    pid_t pid;
    
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }
    if (pid > 0) {
        exit(0);//父进程退出
    }
    fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    //将标准流重定向到/dev/null
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2) {
        close(fd);
    }
    
    setsid();
    
    //chdir("/");
    //umask(0);//确定不会产生文件关闭umask
    
    return 0;
}


int main(int argc, const char * argv[]) {
    
    int i;
    
    if (daemonize()) {
        exit(1);
    }
    
    FILE *fp = fopen(FNAME, "w");
    
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    
    for (i = 0; ; i++) {
        fprintf(fp, "%d\n", i);
        fflush(fp);
        sleep(1);
    }

    
}

//tail -f daemon.txt
//kill pid杀死守护进程
