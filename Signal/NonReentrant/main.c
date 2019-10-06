//
//  main.c
//  NonReentrant
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void my_alarm(int signo)
{
    struct passwd *rootptr;
    
    printf("in sgnal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        printf("getpwnam error\n");
    }
    alarm(1);
}

int main(int argc, const char * argv[])
{

    struct passwd *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for (; ; )
    {
        if ((ptr = getpwnam("sar")) == NULL)
        {
            printf("getpwnam error\n");
        }
        if (strcmp(ptr->pw_name, "sar") != 0)
        {
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }
    
    
    
    
}
