//
//  main.c
//  ErgodicDirImpru
//
//  Created by 杨俊艺 on 2019/6/15.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void printdir(const char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    
    if ((dp = opendir(dir)) == NULL)
    {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);//如果目录存在则进入指定目录
    while ((entry = readdir(dp)) != NULL)//如果检查到目录流中的下一个目录项不为空
    {
        lstat(entry->d_name, &statbuf);//查找刚得到的这个目录项的信息并保存到状态缓冲区
        if (S_ISDIR(statbuf.st_mode))//S_ISDIR宏测试是不是一个目录
        {
            //如果找到的是目录跳过前两个.和..
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
            {
                continue;
            }
            printf("%*s%s/\n", depth, "", entry->d_name);//%*s以及depth参数是用来控制缩进的
            //递归新的缩进级别
            printdir(entry->d_name, depth + 4);
        }
        else//如果不是目录直接打印出名字
            printf("%*s%s/\n", depth, "", entry->d_name);
    }
    chdir("..");//返回上一级
    closedir(dp);//关闭目录释放资源
}

int main(int argc, const char * argv[])
{
    
    const char *topdir = ".";//默认使用当前文件夹,也可以使用命令行参数指定要遍历的文件夹
    if (argc >= 2) {
        topdir = argv[1];
    }
    printf("topdir scan of %s:\n", topdir);
    printdir(topdir, 0);
    printf("done.\n");
    
    
    
    
    return 0;
}
