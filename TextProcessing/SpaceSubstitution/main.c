//
//  main.c
//  SpaceSubstitution
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    
    int c, lastc;
    
    lastc = 'a';//初始化为任意一个非空格字符
//    while ((c = getchar()) != EOF)//版本一
//    {
//        if (c != ' ')
//            putchar(c);
//        if (c == ' ')
//            if (lastc != ' ')
//                putchar(c);
//        lastc = c;
//    }
//
    while ((c = getchar()) != EOF)//版本二
    {
        if (c!=' '||lastc!=' ')//如果c是空格且最后刚输出的是空格,那么不输出此次的空格
        {
            putchar(c);
        }
        lastc = c;
    }
    

    return 0;
}

//将输入复制到输出,连续空格使用一个空格代替
