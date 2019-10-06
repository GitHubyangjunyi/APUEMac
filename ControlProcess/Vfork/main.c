//
//  main.c
//  Vfork
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int globvar = 6;

int main(int argc, const char * argv[])
{
    int var;
    pid_t pid;
    
    var = 88;
    
    printf("before vfork!\n");//不刷新缓冲
    
    if ((pid = vfork()) < 0) {
        perror("vfork error");
    }else if (pid == 0){
        globvar++;
        var++;
        //printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
        _exit(0);//使用_exit而不是exit,因为_exit并不会冲洗标准I/O缓冲区,如果调用的是exit而不是_exit则输出结果是不确定的
        //依赖于标准库的实现,可能会看到输出没有变化,或者没有父进程的输出
    }
    
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    
    
    exit(0);
    
}

//
