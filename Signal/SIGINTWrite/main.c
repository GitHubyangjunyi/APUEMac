//
//  main.c
//  SIGINTWrite
//
//  Created by 杨俊艺 on 2019/9/19.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void init_handler(int s)
{
    write(1, "!", 1);
}

int main(int argc, const char * argv[]) {
    
    int i;
    
    signal(SIGINT, init_handler);
    
    for (i = 0; i < 10; i++) {
        write(1, "X", 1);
        sleep(4);
    }
    
    
    
    return 0;
}

//应该使用终端运行./SIGINTWrite
//由于信号会打断阻塞的系统调用,所以如果程序运行时一直发送Ctrl+C则会加速程序执行
