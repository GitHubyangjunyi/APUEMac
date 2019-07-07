//
//  main.c
//  ArrayPointer
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int arr[3] = { 1,2,3 };
    
    int *p = arr;
    for ( ; p != arr + 3;p++)
    {
        printf("%d\n", *p);
    }
    
    printf("sizeof(arr) = %d\n", sizeof(arr));
    printf("sizeof(p) = %d\n", sizeof(p));
    printf("sizeof(*p) = %d\n", sizeof(*p));
    printf("sizeof(&p) = %d\n", sizeof(&p));
    
    
    printf("%p\n", &p);
    
    
    
    
    return 0;
}

//p[n] == *(p + n)
//p[n][m] == *(*(p + n) + m)
