//
//  main.c
//  Fflush
//
//  Created by 杨俊艺 on 2019/9/9.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    putchar('a');
    write(1, "b", 1);
    
    putchar('a');
    write(1, "b", 1);
    
    putchar('a');
    write(1, "b", 1);
    
    
    
    
    return 0;
}

//在Linux下可能输出bbbaaa
//strace ./Fflush跟踪
