//
//  main.c
//  Atexit
//
//  Created by 杨俊艺 on 2019/9/14.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

static void exit1(void);
static void exit2(void);

int main(int argc, const char * argv[]) {
    
    if (atexit(exit2) != 0) {
        printf("can't register exit1!\n");
    }
    
    if (atexit(exit1) != 0) {
        printf("can't register exit1!\n");
    }
    if (atexit(exit1) != 0) {
        printf("can't register exit1!\n");
    }
    
    
    
    return 0;
}

static void exit1(void)
{
    printf("exit1!\n");
}

static void exit2(void)
{
    printf("exit2!\n");
}
