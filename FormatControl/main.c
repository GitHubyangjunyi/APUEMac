//
//  main.c
//  FormatControl
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    printf("hello, world\
           \n\
           \n");//如果必须要换行以利于排版,必须使用续行符\避免编译错误
    printf("xxx\007\?\c\n");//\7将发出一声短蜂鸣,在\的后面至多可以使用3个八进制数来代表一个字符,而\7在ASCII字符集中代表一声短蜂鸣
    int onehundred = 100;
    printf("dec = %d;\t     octal = %o;\t     hex = %x\n", onehundred, onehundred, onehundred);
    //如果要在八进制和十六进制前面显示前缀,转换说明加#,C允许使用大写或小写的常量后缀,但是转换说明只能小写
    printf("dec = %d;\t     octal = %#o;\t     hex = %#x\n", onehundred, onehundred, onehundred);
    
    
    return 0;
}

//前面是宽度,后面是精度,格式说明可以省略宽度和精度
//%3d 3个字宽,向右对齐
//%6d 6个字宽,向右对齐
//%3.0f 至少占3个字宽且不带小数点和小数部分,向右对齐
//%6.1f 至少占6个字宽且小数点后有1个小数,向右对齐
//%6f 至少占6个字宽
//%.2f表示小数点后2位小数,宽度没有限制
//%.0f表示强制不打印小数点和小数部分
//
//%o 八进制
//%x 十六进制
//%c 字符
//%s 字符串
//%% 表示%本身
