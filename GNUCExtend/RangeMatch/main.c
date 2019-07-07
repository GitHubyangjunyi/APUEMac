//
//  main.c
//  RangeMatch
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int i = 4;
    switch (i)
    {
        case 1:
            printf("1\n");
            break;
        case 2 ... 8:
            printf("%d\n", i);
            break;
        case 9:
            printf("9\n");
            break;
        default:
            break;
    }
    
    return 0;
}

//范围匹配
//2 ... 8
//...和其两端的数据范围2和8之间也要空格
