//
//  main.c
//  Fork
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int globvar = 6;
char buf[] = "a write to stdout!\n";

int main(int argc, const char * argv[])
{
    int var;
    pid_t pid;
    
    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        perror("write error");
    }
    printf("before fork!\n");//不刷新缓冲
    
    if ((pid = fork()) < 0) {
        perror("fork error");
    }else if (pid == 0){
        globvar++;
        var++;
    }else{
        sleep(2);
    }
    
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    
    
    exit(0);
    
}

//fork不改变父进程的变量值
//不刷新缓冲区将导致
//./Fork > a
//a write to stdout!
//before fork!
//pid = 729, glob = 7, var = 89
//before fork!
//pid = 728, glob = 6, var = 88
