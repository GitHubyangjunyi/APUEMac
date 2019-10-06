//
//  main.c
//  Environ
//
//  Created by 杨俊艺 on 2019/9/14.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

extern char **environ;//每个程序都会接受一张环境表,也是一个字符指针数组,全局变量environ包含该数组指针的地址

int main(int argc, const char * argv[]) {
    
    for (int i = 0; environ[i] != NULL; i++) {
        puts(environ[i]);
    }
    
    puts(getenv("PATH"));
    
    exit(0);
    
}
