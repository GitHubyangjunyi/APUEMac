//
//  main.c
//  Strlen
//
//  Created by 杨俊艺 on 2019/8/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int strlenx(char *s);
size_t strlenp(char *s);

int main(int argc, const char * argv[])
{
    
    printf("%d\n", strlenx("xx"));
 
    char arr[4] = "123";
    printf("%d\n", strlenx(arr));
    
    
    char arrx[4] = "1234";
    printf("%d\n", strlenx(arrx));//出错
    
    char *ptr = &arr[1];
    printf("%d\n", strlenx(ptr));
    
    printf("%d\n", (int)strlenp("xx"));
    
    
    
    
    return 0;
}

int strlenx(char *s)//在函数定义中,形式参数char *s和char s[]作用一样
{
    int n;
    
    for (n = 0; *s != '\0'; s++)
    {
        n++;
    }
    return n;
}

size_t strlenp(char *s)
{
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}

//头文件stddef.h中定义的类型ptrdiff_t足以表示两个指针之间的带符号差值,这里使用size_t为了跟标准库中的函数版本相匹配
//size_t是由sizeof返回的无符号整型
