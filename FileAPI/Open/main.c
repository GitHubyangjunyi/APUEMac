//
//  main.c
//  Open
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char * argv[]) {
    
    open("myfile", O_CREAT, S_IRUSR | S_IXOTH);//请求属主可读，其他用户可执行
    open("myfilex", O_CREAT, S_IRUSR | S_IWGRP | S_IWOTH | S_IXOTH);//请求属主可读，组可写，其他用户可写可执行
    //umask值是0022（八进制），所以文件所属组和其他用户都不能写这个文件，即使明确指定要创建文件所属组和其他用户都能写的情况下
    open("x", O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);//请求全部权限
    //测试文件代表的不是一个目录且只设置了属主执行权限
    open("myfiles", O_CREAT, S_IXUSR);//请求属主可执行
    struct stat statbuf;
    mode_t modes;
    
    stat("myfiles", &statbuf);
    modes = statbuf.st_mode;
    if (!S_ISDIR(modes) && (modes & S_IRWXU) == S_IXUSR)
    {
        printf("pass!\n");
    }
    else
    {
        printf("fail!\n");
    }
    
    
    
    
    
    return 0;
}

//open建立了一条到文件或设备的访问路径，如果调用成功则返回一个可以被其他系统调用使用的唯一的文件描述符
//文件描述符是唯一的并且不会与其他运行中的程序共享
//如果两个进程同时打开了同一个文件则会得到不同的文件描述符，如果他们对文件进行写操作，则是各写各大
//分别接着上次离开的地方写数据，彼此之间相互覆盖，两个程序对文件的读写位置不同，可以使用文件锁防止冲突
//umask权限相关
//-r-------x  1 yangjunyi  staff      0  6 12 14:34 myfile
//-r-------x  1 yangjunyi  staff      0  6 12 14:34 myfilex
//-rwxr-xr-x  1 yangjunyi  staff      0  6 12 14:34 x

