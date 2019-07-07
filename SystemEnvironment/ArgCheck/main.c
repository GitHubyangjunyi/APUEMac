//
//  main.c
//  ArgCheck
//
//  Created by 杨俊艺 on 2019/6/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    int arg;
    for (arg = 0; arg < argc; arg++) {
        if (argv[arg][0] == '-')
            printf("option: %s\n", argv[arg] + 1);//加上一跳过字符-
        else
            printf("argument %d: %s\n", arg, argv[arg]);
    }
    
    
    
    
    return 0;
}

//这个程序利用计数参数argc建立一个循环来检查所有的程序参数
//它通过检查首字母是否是短横线来发现选项
//在本例中如果打算支持l选项和r选项那么我们就忽略了一个事实,lr选项应该和-l -r一样处理
//X/Open规范定义了命令行选项的标准用法的同时定义了在C语言程序中提供命令行开关的标准编程接口getopt函数
//./ArgCheck -i -lr 'hi there' -f fred.c
//argument 0: ./ArgCheck
//option: i
//option: lr
//argument 3: hi there
//option: f
//argument 5: fred.c
