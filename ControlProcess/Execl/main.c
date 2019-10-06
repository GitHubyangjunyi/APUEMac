//
//  main.c
//  Execl
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    puts("Begin!");
    
    fflush(NULL);
    
    execl("/bin/date", "date", "+%s", NULL);
    perror("execl");
    exit(1);
    
    puts("End!");
    
    
    exit(0);
}

//在终端运行./Execl
