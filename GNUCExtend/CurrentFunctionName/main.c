//
//  main.c
//  CurrentFunctionName
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    

    printf("the function name is %s\n", __FUNCTION__);
    printf("the function name is %s\n", __func__);
    //printf("the function name is %s\n", __PRETTY_FUNCTION__);
    
    printf("the function line is %d\n", __LINE__);//行号
    printf("the file is %s\n", __FILE__);//文件绝对路径
    printf("the date is %s\n", __DATE__);//当前日期
    printf("the time is %s\n", __TIME__);//当前时间
    
    
    
    return 0;
}

//GNU C为当前函数的名字准备了两个标识符,分别是__PRETTY_FUNCTION__和__FUNCTION__,其中__FUNCTION__标识符保存着函数在源码中的名字
//__PRETTY_FUNCTION__则保存着带有语言特色的名字,在C函数中,两个标识符代表的函数名字相同
//在C99标准中,只规定了__func__能够代表函数的名字,而__FUNCTION__最然被各类编译器支持,但只是__func__标识符的宏别名
