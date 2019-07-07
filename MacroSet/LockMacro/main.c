//
//  main.c
//  LockMacro
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define SYSTEM_LOCK() \
{\
    unsigned long state;\
    state=1;\
    printf("%d\r\n",state);
#define SYSTEM_UNLOCK() \
        state=0;\
        printf("%d\r\n",state);\
}

int main(int argc, const char * argv[]) {
    
    SYSTEM_LOCK();
    SYSTEM_UNLOCK();
    
    SYSTEM_LOCK(); SYSTEM_UNLOCK();
    
    char GETCHAR = getchar();
    printf("%c\n", GETCHAR);
    
    return 0;
}

//单独使用SYSTEM_LOCK()或SYSTEM_UNLOCK()调用编译出错
//可以实现临界区,可以实现线程安全,而且这对宏利用了C语法编译检查,强制成对使用,同时避免了加锁解锁不成对造成的死锁问题
