//
//  main.c
//  Lseek
//
//  Created by 杨俊艺 on 2019/9/6.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define    FILE_MODE    (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, const char * argv[]) {
    
    int fd;
    
    if ((fd = creat("file.hole", FILE_MODE)) < 0) {
        printf("CREAT ERROR!");
    }
    
    if (write(fd, buf1, 10) != 10) {
        printf("buf1 write error!");
    }
    //现在文件偏移10
    
    if (lseek(fd, 16384, SEEK_SET) == -1) {
        printf("lseek error!");
    }
    //现在文件偏移16384
    
    if (write(fd, buf2, 10) != 10) {
        printf("buf2 write error!");
    }
    //现在文件偏移16394
    
    return 0;
}

//yangjunyideMac-mini:Debug yangjunyi$ ls -l file.hole
//-rw-r--r--  1 yangjunyi  staff  16394  9  6 15:25 file.hole
//yangjunyideMac-mini:Debug yangjunyi$ od -c file.hole
//0000000    a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
//0000020   \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
//*
//0040000    A   B   C   D   E   F   G   H   I   J
//0040012
//
//注意事项:
//lseek只修改文件表项中的当前文件偏移量,不进行I/O操作
