//
//  main.c
//  Alarm
//
//  Created by 杨俊艺 on 2019/9/19.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    alarm(10);
    alarm(5);
    alarm(1);
    //使用多个计时器会引发bug
    //只有最后一个生效,响应信号将退出程序
    
    while (1) {
        //pause();
    }
    
    
    
    
    return 0;
}

//使用终端运行
//尽量使用alarm而不是使用sleep
//因为有的环境下sleep使用alarm + pause实现的
//Linux环境下sleep用nanosleep封装没问题
