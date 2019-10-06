//
//  main.c
//  Time
//
//  Created by 杨俊艺 on 2019/9/14.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <time.h>
#include <sys/types.h>

#define FNAME "./time.txt"
#define BUFSIZE 1024

int main(int argc, const char * argv[]) {
    
    FILE *fp, *fo;
    char buf[BUFSIZE];
    int count = 0;
    time_t stamp;
    struct tm *stm;

    fp = fopen(FNAME, "a+");
    fo = fopen(FNAME, "r");
    if (fp == NULL) {
        perror("fopen():");
    }

    while (fgets(buf, BUFSIZE, fo) != NULL) {//如果使用的是以a+形式打开的fp将导致每次运行时行号重新以1开始计数而不是从当前是第几行开始,所以使用另一个文件流来计数
        count++;
    }

    while (1) {
        time(&stamp);
        stm = localtime(&stamp);

        fprintf(fp, "%-4d%d-%d-%d %d:%d:%d\n", ++count, stm->tm_year + 1900, stm->tm_mon + 1, stm->tm_mday, stm->tm_hour, stm->tm_min, stm->tm_sec);
        //除了标准终端设备,其他默认全缓冲,所以time.txt文件中无内容
        fflush(fp);
        sleep(1);
    }
    
    
    
    //下面的独立程序计算当前时间的100天后
//    time_t stamp;
//    struct tm *stm;
//    char timerstr[BUFSIZE];
//
//    time(&stamp);
//    stm = localtime(&stamp);
//    strftime(timerstr, BUFSIZE, "NOW:%Y-%m-%d", stm);
//    puts(timerstr);
//
//    stm->tm_mday += 100;
//    (void)mktime(stm);//mktime会先判断stm是否合法,不合法将自动调整
//    strftime(timerstr, BUFSIZE, "100 days laer:%Y-%m-%d", stm);
//    puts(timerstr);
//
    
    return 0;
}

//动态查看文件尾
//tail -f time.txt
