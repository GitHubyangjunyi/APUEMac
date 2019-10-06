//
//  main.c
//  TokenBucketLib
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
#include "TokenBucket.h"

#define BUFSIZE 1024
#define CPS     10
#define BURST   100

int main(int argc, const char * argv[])
{
    
    int sfd,dfd = 1;//标准输出文件描述符1
    char buf[BUFSIZE];
    long len,ret,pos;
    TokenBucket_t *tb;
    int size;
    
    if (argc < 2) {//参数3变成2
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    
    tb = TokenBucket_Init(CPS, BURST);
    if (tb == NULL) {
        fprintf(stderr, "TokenBucket_Init Failed!");
        exit(1);
    }
    
    do {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0) {
            if (errno != EINTR) {//并不是被信号打断而导致的假错误
                perror("open:");
                exit(1);
            }
        }
    } while (sfd < 0);
    
    while (1) {
        size = TokenBucket_FetchToken(tb, BUFSIZE);
        if (size < 0) {
            fprintf(stderr, "TokenBucket_FetchToken Failed!");
            exit(1);
        }
        
        while ((len = read(sfd, buf, size)) < 0)//读取成功返回读到的字节数,到达文件尾端返回0
        {
            if (errno == EINTR)
                continue;//如果读取时一直被打断导致没有数据读到将一直死等,直到读取到数据或者到达文件尾
            perror("read: ");
            break;
        }
        if (len == 0) {
            break;
        }
        
        if (size - len > 0) {
            TokenBucket_ReturnToken(tb, size - (int)len);
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
    }
    
    printf("\n");
    close(sfd);
    TokenBucket_Destory(tb);//销毁令牌桶
    
    exit(0);
}

//令牌桶封装成库
//整体框架来自CatImplementationTimeControlTokenBucket
//实现流量控制算法的令牌桶
//每秒钟固定cat多少个字节
//这里使用信号机制
//将会很占用处理器资源,所以while处使用pause
//如果不使用pause,则在Mac mini 2018上将会多占用大约10%的处理器资源
