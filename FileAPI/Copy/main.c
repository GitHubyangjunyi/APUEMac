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
    while ((nread = read(in, block, sizeof(block))) > 0)
    {
        write(out, block, nread);
    }
    
    
    
    return 0;
}

//命令行
//TIMEFORMAT="" time ./copy

