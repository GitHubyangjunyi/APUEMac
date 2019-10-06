//
//  main.c
//  ExeclSleep
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, const char * argv[]) {
    
    pid_t pid;
    
    puts("Begin!");
    
    fflush(NULL);
    
    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }else if (pid == 0)
    {
        execl("/bin/sleep", "sleep", "10", NULL);
        perror("execl");
        exit(1);
    }
    
    wait(NULL);
    
    puts("End!");
    
    exit(0);
}

