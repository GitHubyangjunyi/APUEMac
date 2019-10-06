//
//  main.c
//  MultiprocessingPrimeCrossPartition
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define LEFT 30000000
#define RIGHT 30000200
#define N 3

int main(int argc, const char * argv[]) {
    
    pid_t pid;
    int i, j, mark, n;
    
    for (n = 0; n < N; n++)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork error!\n");
            for (i = 0; i < N; i++)
            {
                wait(NULL);
            }
            exit(1);
        }else if (pid == 0)
        {
            for (i = LEFT + n; i <= RIGHT; i+=N)
            {
                mark = 1;
                for (j = 2; j < i/2; j++)
                {
                    if (i % j == 0)
                    {
                        mark = 0;
                        break;
                    }
                }
                if (mark)
                {
                    printf("process[%d] %d is prime\n", n, i);//第一个子进程永远拿不到素数
                }
            }
            exit(0);//子进程计算完退出
        }
    }
    
    //int status;
    for (i = 0; i < N; i++)
    {
        wait(NULL);
    }
    //会增加运行时间
    
    exit(0);//父进程退出
}
