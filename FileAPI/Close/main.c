//
//  main.c
//  Close
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char * argv[]) {
    
    int x = open("myfixxle", O_CREAT, S_IRUSR | S_IXOTH);//请求属主可读，其他用户可执行
    printf("%d\n", x);
    
    close(x);//系统调用close用于终止文件描述符与其对应文件的关联，文件描述符被释放并能够重新利用
    
    printf("%d\n", x);
    
    
    return 0;
}
