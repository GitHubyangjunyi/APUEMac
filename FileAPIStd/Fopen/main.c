//
//  main.c
//  Fopen
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {
    
    FILE *fps,*fpd;
    int ch;
    
    if (argc < 3) {
        fprintf(stderr, "Usage:%s <src_file> <dest_file>\n",  argv[0]);
        exit(1);
    }
    
    fps=fopen(argv[1], "r");//用r而不是r+是为了保证源文件存在
    if (fps == NULL) {
        perror("fopen()");
        exit(1);
    }
    fpd =fopen(argv[2], "w");
    if (fpd == NULL) {
        fclose(fps);//还可以使用钩子函数防止内存泄漏
        perror("fopen()");
        exit(1);
    }
    while (1) {
        ch = fgetc(fps);
        if (ch == EOF) {
            break;
        }
        fputc(ch, fpd);
    }
    
    fclose(fps);
    fclose(fpd);
    
    
    
    
    
    
    
    return 0;
}
