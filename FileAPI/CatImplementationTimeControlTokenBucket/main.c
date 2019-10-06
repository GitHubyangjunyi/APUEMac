//
//  main.c
//  CatImplementationTimeControlTokenBucket
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFSIZE 10
#define CPS     10
#define BURST   100

static volatile sig_atomic_t token = 0;

static void alarm_handler(int s)
{
    alarm(1);
    token++;
    if (token > BURST) {
        token = BURST;//保持令牌上限
    }
}

int main(int argc, const char * argv[])
{
    
    int sfd,dfd = 1;//标准输出文件描述符1
    char buf[BUFSIZE];
    long len,ret,pos;
    
    
    if (argc < 2) {//参数3变成2
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    
    //
    signal(SIGALRM, alarm_handler);
    alarm(1);
    //
    
    do {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0) {
            if (errno != EINTR) {//并不是被信号打断而导致的假错误
                perror("open:");
                exit(1);
            }
        }
    } while (sfd < 0);
    
    //    do {
    //        dfd = open(argv[2], O_WRONLY | O_CREAT, O_TRUNC, 0600);
    //        if (dfd < 0) {
    //            if (errno != EINTR) {
    //                close(sfd);
    //                perror("open: ");
    //                exit(2);
    //            }
    //        }
    //    } while (dfd < 0);
    
    while (1) {
        
        //当token小于等于0时pause,但是当程序正在判断token,刚判断完还没来得及pause,alarm信号就到来了
        //
        //
        while (token <= 0) {//检测令牌数
            //                          <---------alarm信号到来点,token变为1,无伤大雅,因为是令牌桶
            pause();//减少资源占用        <---------但是有可能这里要token--,而上面信号在token++,虽然不太可能,不太可能的原因是因为pause时一定会被信号打断,下来马上token--了,而token++差不多在一秒后做
        }
        token--;//                      <--------问题出在这里比如token本来是1,然后--操作还没来得及回写,被信号打断,然后信号处理那边将token++后变成2且写入内存,然后这里又继续执行,把1覆盖回去,导致最终值是1
                //                      <--------改为static volatile sig_atomic_t token = 0; 
        while ((len = read(sfd, buf, BUFSIZE)) < 0)//读取成功返回读到的字节数,到达文件尾端返回0
        {
            if (errno == EINTR)
                continue;//如果读取时一直被打断导致没有数据读到将一直死等,直到读取到数据或者到达文件尾
            perror("read: ");
            break;
        }
        if (len == 0) {
            break;
        }
        pos = 0;
        while (len > 0) {//如果没有完全写完则重复写
            ret = write(dfd, buf + pos, len);
            if (ret < 0) {
                if (errno == EINTR)
                    continue;
                perror("write:");
                exit(3);
            }
            pos += ret;
            len -= ret;
        }
        //sleep(1);//不好的写法,sleep的不同的实现将导致可移植性以及正确性
    }
    
    printf("\n");
    //close(dfd);
    close(sfd);
    
    exit(0);
}

//整体框架来自CatImplementationTimeControlAlarm
//实现流量控制算法的令牌桶
//每秒钟固定cat多少个字节
//这里使用信号机制
//将会很占用处理器资源,所以while处使用pause
//如果不使用pause,则在Mac mini 2018上将会多占用大约10%的处理器资源
