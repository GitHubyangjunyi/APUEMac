//
//  main.c
//  SystemImplementation
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
   
    
    
    
    printf("%ld\n", sysconf(_SC_PAGESIZE));
    
    
    
    
    
    return 0;
}
