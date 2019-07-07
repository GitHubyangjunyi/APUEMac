//
//  main.c
//  GNUCMacroExtend
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

//当我们定义一个变参宏时除了使用预定义标识符__VA_ARGS__表示变参列表外,还可以使用下面这种写法
#define LOG(fmt,args...) printf(fmt, args)

//使用预定义标识符__VA_ARGS__来定义一个变参宏是C99标准规定的写法,而上面这种格式是GNU C扩展的一个新写法
//我们不再使用__VA_ARGS__而是直接使用args...来表示一个变参列表,然后在后面的宏定义中直接使用args代表变参列表就可以了
//跟之前一样为了避免变参列表为空时的语法错误,我们也需要添加一个连接符##
#define LOGFIX(fmt,args...) printf(fmt, ##args)

//使用这种方式你会发现比使用__VA_ARGS__看起来更加直观和方便

int main(int argc, const char * argv[]) {
    
    
    LOGFIX("LOGFIX:    hello\n");
    
    
    
    return 0;
}
