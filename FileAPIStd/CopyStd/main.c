//
//  main.c
//  CopyStd
//
//  Created by 杨俊艺 on 2019/6/13.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    int c;
    FILE *in, *out;
    
    in = fopen("file.in", "r");
    out = fopen("file.out", "w");
    
    while ((c = fgetc(in)) != EOF) {
        fputc(c, out);
    }
    
    
    return 0;
}

//这个程序虽然不如底层数据块复制版本块,但是比一次复制一个字符快
//原因是因为stdlib库在FILE结构中使用了一个内部缓冲区,只有在缓冲区满时才进行底层系统调用
