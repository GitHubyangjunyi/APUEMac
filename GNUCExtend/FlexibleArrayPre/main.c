//
//  main.c
//  FlexibleArrayPre
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

struct Buffer
{
    int len;
    int a[0];
};

int main(int argc, const char * argv[]) {
    

    struct Buffer *buf = (struct Buffer *)malloc(sizeof(struct Buffer) + 20);
    buf->len = 20;
    strcpy(buf->a, "hello wanglitao!\n");
    puts(buf->a);
    printf("\n");
    
    strcpy(buf->a, "hello wanglitaox\0xx!\n");
    puts(buf->a);
    
    free(buf);
    
    
    
    return 0;
}

//通过这种灵活的动态内存申请得到的这个buﬀer结构体表示的一片内存缓冲区就可以随时调整,这个特性在一些场合非常有用
//比如在线视频网站都支持多种格式的视频播放:普清/高清/超清/1080P/蓝光甚至4K,如果我们本地程序需要在内存中申请一个buﬀer用来缓存解码后的视频数据
//那么不同的播放格式需要的buﬀer大小是不一样的,如果我们按照4K的标准去申请内存,那么当播放普清视频时就用不了这么大的缓冲区
//而使用变长结构体我们就可以根据用户的播放格式设置灵活地申请不同大小的buﬀer节省内存空间
//零长度数组在内核中一般以变长结构体的形式使用
//我们就分析一下Linux内核中的USB驱动,在网卡驱动中大家可能都比较熟悉一个名字:套接字缓冲区,即socket buﬀer,用来传输网络数据包
//同样在USB驱动中也有一个类似的东西叫URB,其全名为USB Request Block,即USB请求块,用来传输USB数据包
