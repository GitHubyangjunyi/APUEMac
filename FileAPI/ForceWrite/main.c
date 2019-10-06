//
//  main.c
//  ForceWrite
//
//  Created by 杨俊艺 on 2019/9/10.
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

#define BUFSIZE 1024

int main(int argc, const char * argv[]) {
    
    
//    int sfd,dfd;
//    char buf[BUFSIZE];
//    long len,ret,pos;
//
//
//    if (argc < 3) {
//        fprintf(stderr, "Usage...\n");
//    }
//
//    sfd = open(argv[1], O_RDONLY);
//    if (sfd < 0) {
//        exit(1);
//    }
//
//    dfd = open(argv[2], O_WRONLY | O_CREAT, O_TRUNC, 0600);
//    if (dfd < 0) {
//        close(sfd);
//        perror("open: ");
//        exit(2);
//    }
//
//    while (1) {
//        len = read(sfd, buf, BUFSIZE);
//        if (len < 0) {
//            perror("read: ");
//            break;
//        }
//        if (len == 0) {
//            break;
//        }
//        pos = 0;
//        while (len > 0) {//如果没有完全写完则重复写
//            ret = write(dfd, buf + pos, len);
//            if (ret < 0) {
//                perror("write:");
//                exit(3);
//            }
//            pos += ret;
//            len -= ret;
//        }
//    }
//
//    close(dfd);
//    close(sfd);
//
//    exit(0);
    
    
    int sfd,dfd;
    char buf[BUFSIZE];
    long len,ret,pos;
    
    
    if (argc < 3) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    
    //open返回-1表示出错并会设置errno
    do {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0) {
            if (errno != EINTR) {//并不是被信号打断导致的假错误而是真错误就报错退出,否则再次尝试open
                perror("open:");
                exit(1);
            }
        }
    } while (sfd < 0);
    
    do {
        dfd = open(argv[2], O_WRONLY | O_CREAT, O_TRUNC, 0600);
        if (dfd < 0) {
            if (errno != EINTR) {
                close(sfd);
                perror("open: ");
                exit(2);
            }
        }
    } while (dfd < 0);
    
    while (1)
    {
        len = read(sfd, buf, BUFSIZE);//读取成功返回读到的字节数,到达文件尾端返回0
        if (len < 0)
        {
            if (errno == EINTR)
                continue;//如果读取时一直被打断导致没有数据读到将一直死等,直到读取到数据或者到达文件尾
            perror("read: ");//确实是读取错误报错退出
            break;
        }
        if (len == 0)//读到文件尾了退出循环
        {
            break;
        }
        pos = 0;
        while (len > 0)//如果没有完全写完则重复写
        {
            ret = write(dfd, buf + pos, len);//BSD派生的实现则处理为部分成功返回已经写入的字节数,详情查看man 2 write
            if (ret < 0)
            {
                if (errno == EINTR)//如果是被打断的,则continue重新写
                    continue;
                perror("write:");
                exit(3);
            }
            pos += ret;
            len -= ret;
        }
    }
    
    close(dfd);
    close(sfd);
    
    exit(0);
    
}

//由于信号会打断阻塞的系统调用,所以这里的文件I/O程序没有一个是正确的
//进行重构
