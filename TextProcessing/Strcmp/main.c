//
//  main.c
//  Strcmp
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    char str1[15];
    char str2[15];
    
    strcpy(str1, "abcdef");
    strcpy(str2, "ABCDEFG");
    
    int ret = strcmp(str1, str2);
    
    if (ret < 0)
    {
        printf("str1 < str2\n");
    }
    else if (ret > 0)
    {
        printf("str1 > str2\n");
    }
    else
    {
        printf("str1 == str2\n");
    }

    
    return 0;
}
