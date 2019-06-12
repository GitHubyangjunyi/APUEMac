//
//  main.c
//  Write
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    write(1, "<#const void *__buf#>", 19);
    
    
    
    return 0;
}

//系统调用write的作用是把缓冲区buf的前n字节写入与文件描述符files相关的文件中并返回实际写入的字节数
//返回0表示未写入数据
//返回-1表示出错
//wtite可能报告写入的字节比要求的少，但这并不一定是错误，需要检查errno以发现错误并再次调用write
