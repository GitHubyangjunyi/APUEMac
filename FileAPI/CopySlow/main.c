//
//  main.c
//  CopySlow
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
    char c;
    int in, out;
    
    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);//只允许属主读写
    while (read(in, &c, 1) == 1)//一个一个字节进行读写转移
    {
        write(out, &c, 1);
    }
    
    
    return 0;
}
