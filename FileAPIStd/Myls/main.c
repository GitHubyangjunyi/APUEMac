//
//  main.c
//  Myls
//
//  Created by 杨俊艺 on 2019/9/5.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    DIR *dp;
    struct dirent *dirp;
    
    if (argc != 2) {
        printf("usage: ls directory_name ");
    }
    
    if ((dp = opendir(argv[1])) == NULL)//opendir函数返回指向DIR结构的指针,由dp接收
        printf("can't open %s",argv[1]);
    
    while((dirp = readdir(dp)) != NULL)//readdir读取每个目录项,返回一个指向dirent结构的指针,由dirp接收
        printf("%s\n",dirp->d_name);//从dirent结构中取出目录名
    
    closedir(dp);
    
    exit(0);
}
