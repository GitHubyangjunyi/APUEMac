//
//  main.c
//  Stat
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char * argv[])
{
    //测试文件代表的不是一个目录且只设置了属主执行权限
    open("myfiles", O_CREAT, S_IXUSR);//请求属主可执行
    struct stat statbuf;
    mode_t modes;
    
    stat("myfiles", &statbuf);//返回通过文件名查找到的状态信息并保存到statbuf缓冲区
    modes = statbuf.st_mode;
    if (!S_ISDIR(modes) && (modes & S_IRWXU) == S_IXUSR)//文件不是一个目录并且属主具有执行权限
    {
        printf("pass!\n");
    }
    else
    {
        printf("fail!\n");
    }
    
    
    
    
    
    return 0;
}
