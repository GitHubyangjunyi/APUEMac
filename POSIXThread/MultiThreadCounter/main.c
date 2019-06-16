//
//  main.c
//  MultiThreadCounter
//
//  Created by 杨俊艺 on 2019/6/13.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LOOPS 10000000
//使用比较大的数保证第一个线程不要在第二个线程运行前退出

static int counter = 0;

static void *thread(void *unused)
{
    int i;
    for (i = 0; i < LOOPS; ++i) {
        ++counter;
    }
    return NULL;
}

int main(int argc, const char * argv[])
{
    pthread_t t1 = NULL;
    pthread_t t2 = NULL;
    
    pthread_create(&t1, NULL, thread, NULL);
    pthread_create(&t2, NULL, thread, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Counter is %d by thread\n", counter);
    
    
    return 0;
}
