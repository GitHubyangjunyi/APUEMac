//
//  main.c
//  Memset
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int a[5] = { 1, 2, 3, 4, 5 };
    memset(a, 0, sizeof(a));
    
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    memset(a, 1, sizeof(a));
    
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    
    return 0;
}

//memset函数
//memset函数的格式为
//memset(数组名, 值, sizeof(数组名));
//memset函数第一个参数是指向要填充的缓冲区的指针,第二个参数是填充缓冲区的值,最后一个参数是要填充的字节数
//因为memset是按字节赋值,对每个字节赋值同样的值,这样int四个字节会附相同的值,而0二进制代码全为0,-1的二进制补码全为1,不容易错
//所以当赋值为1时1一个字节为0000 0001,int值4个字节0000 0001 0000 0001 0000 0001 0000 00001输出的值转换成10进制也就是16843009
//因此如果对数组当中赋值其他数字时,使用fill函数,但是memset速度会更快
