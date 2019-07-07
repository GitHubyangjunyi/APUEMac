//
//  main.c
//  LineCount
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int c, nl = 0;
    
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            nl++;
        }
    }
    printf("%d\n", nl);
    
    
    return 0;
}

//行统计,输入测试时要使用行首Ctrl+Z来作为结束符而不是回车,如果输入abc(Ctrl+Z)回车(Ctrl+Z)则计0行
//标准库保证输入文本流以行序列的形式出现,每一行均以一个换行符结束,因此统计行数等价于统计换行符的个数
