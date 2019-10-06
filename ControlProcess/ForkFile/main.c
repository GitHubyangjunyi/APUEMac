//
//  main.c
//  ForkFile
//
//  Created by 杨俊艺 on 2019/9/17.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, const char * argv[])
{
    
    int fd;
    pid_t pid;
    char buf[10];

    if ((fd = open("system.txt", O_RDONLY)) < 0)
    {
        perror("open:");
        exit(-1);
    }
    
    if ((pid = fork()) < 0)
    {
        perror("fork:");
        exit(-1);
    }else if (pid == 0)                 //子进程
    {
        read(fd, buf, 2);
        write(STDOUT_FILENO, buf, 2);
    }else                               //父进程
    {
        sleep(2);
        lseek(fd, SEEK_CUR, 1);
        read(fd, buf, 3);
        write(STDOUT_FILENO, buf, 3);
        write(STDOUT_FILENO, "\n", 1);
    }
    
    return 0;
    
}
