//
//  main.c
//  Copy
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <unistd.h>//必须首先出现，因为这里定义的与POSIX规范有关的标志可能会影响其他头文件
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, const char * argv[])
{
    char block[1024];//使用数据块进行读写提高性能
    int in, out;
    long nread;
    
    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);//只允许属主读写
    //系统调用read的作用是从与文件描述符files相关联的文件里读取出n字节数据放入缓冲区buff并返回实际读入的字节数（可能小于请求）
    while ((nread = read(in, block, sizeof(block))) > 0)
    {
        write(out, block, nread);//系统调用write的作用是把缓冲区__buf的前__nbyte字节写入与文件描述符__fd相关的文件中并返回实际写入的字节数
    }
    
    
    
    return 0;
}

//命令行
//TIMEFORMAT="" time ./copy
