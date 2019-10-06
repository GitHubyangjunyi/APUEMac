//
//  main.c
//  AlarmMulti
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

static void f1(void *p);
static void f2(void *p);

int main(int argc, const char * argv[]) {
    
    int job1, job2, job3;
    
    puts("Begin:");
    
    //2秒时打印b
    //5秒时打印a
    //7秒时打印c
    //Begin:End!..bbbaaa..ccc...........
    
    
    
    
    
    
    
    puts("End!");
    
    
    while (1) {
        write(1, ".", 1);
        sleep(1);
    }
    
    
    
    
    exit(0);
}

static void f1(void *p)
{
    printf("f1: %s\n", p);
}

static void f2(void *p)
{
    printf("f2: %s\n", p);
}

//有一个1024长度的任务数组,里面存放各个任务信息的结构体的指针
//任务信息结构体
//      sec     定时时间
//      func    要运行的任务
//      arg     运行参数
//      flag    任务状态
//运行定时任务时每当过了一秒就检查各个任务的定时时间并减去1,如果任务的定时时间变为0则执行func
