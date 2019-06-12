//
//  main.c
//  Read
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    int *buff[128];
    long nread;
    
    nread = read(0, buff, 128);
    if (nread == -1)
    {
        write(2, "error\n", 6);
    }
    if ((write(1, buff, nread)) != nread)
    {
        write(2, "write error", 11);
    }
    
    
    return 0;
}

//系统调用read的作用是从与文件描述符files相关联的文件里读取出n字节数据放入缓冲区buff并返回实际读入的字节数（可能小于请求）
//返回0表示未读入数据已到达文件尾
//返回-1表示出错

