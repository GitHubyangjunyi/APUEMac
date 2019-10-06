//
//  main.c
//  Setuid
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    pid_t pid;
    
    if (argc < 3) {
        fprintf(stderr, "Usage...");
        exit(0);
    }
    
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(1);
    }
    if (pid == 0) {
        setuid(ato(argv[1]));
        execvp(argv[2], argv + 2);
        perror("execvp:");
        exit(1);
    }
    
    wait(NULL);
    
    
    exit(0);
}

//          0表示指定要切换过去的用户id 然后要执行的命令 传递给命令的参数
//使用方式./a.out 0 cat /etc/shadow
//提示权限不够
//切换到root用户
//chown root a.out  将可执行文件所有者更换为root
//chmod u+s a.out   设置执行位执行时使用root身份作为有效身份
