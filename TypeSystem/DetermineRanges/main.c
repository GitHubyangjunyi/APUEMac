//
//  main.c
//  DetermineRanges
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <limits.h>

int main(int argc, const char * argv[]) {
    
    printf("1.直接使用头文件定义获得相应值:\n");
    printf("有符号类型\n");
    printf("signed char min  = %d\t", SCHAR_MIN); printf("8位\n");
    printf("signed char max  = %d\t", SCHAR_MAX); printf("8位\n");
    printf("signed short min = %d\t", SHRT_MIN); printf("16位\n");
    printf("signed short max = %d\t", SHRT_MAX); printf("16位\n");
    printf("signed int min   = %d\t", INT_MIN); printf("32位\n");
    printf("signed int max   = %d\t", INT_MAX); printf("32位\n");
    printf("signed long min  = %ld\t", LONG_MIN); printf("64位\n");
    printf("signed long max  = %ld\t", LONG_MAX); printf("64位\n");
    printf("无符号类型\n");
    printf("unsigned char max  = %u\t", UCHAR_MAX); printf("8位\n");
    printf("unsigned short max = %u\t", USHRT_MAX); printf("16位\n");
    printf("unsigned int max   = %u\t", UINT_MAX); printf("32位\n");
    printf("unsigned long max  = %lu\t", ULONG_MAX); printf("64位\n\n");
    
    
    printf("2.通过计算获得相应值:\n");
    printf("有符号类型\n");
    printf("signed char min  = %d\t", -(char)((unsigned char) ~0 >> 1)); printf("8位\n");
    printf("signed char max  = %d\t", (char)((unsigned char) ~0 >> 1)); printf("8位\n");
    //先将0的各个二进制位全部转换为1,然后将结果值转换为unsigned char类型,,再右移一位清楚符号位,最后转成char类型就得到signed类型字符的最大值
    printf("signed short min = %d\t", -(short)((unsigned short) ~0 >> 1)); printf("16位\n");
    printf("signed short max = %d\t", (short)((unsigned short) ~0 >> 1)); printf("16位\n");
    printf("signed int min   = %d\t", -(int)((unsigned int) ~0 >> 1)); printf("32位\n");
    printf("signed int max   = %d\t", (int)((unsigned int) ~0 >> 1)); printf("32位\n");
    printf("signed long min  = %ld\t", -(long)((unsigned long) ~0 >> 1)); printf("64位\n");
    printf("signed long max  = %ld\t", (long)((unsigned long) ~0 >> 1)); printf("64位\n");
    printf("无符号类型\n");
    printf("unsigned char max  = %u\t", (unsigned char) ~0 ); printf("8位\n");
    printf("unsigned short max = %u\t", (unsigned short)~0 ); printf("16位\n");
    printf("unsigned int max   = %u\t", (unsigned int) ~0 ); printf("32位\n");
    printf("unsigned long max  = %lu\t", (unsigned long) ~0 ); printf("64位\n");
    
    printf("使用sizeof\n");
    printf("%lld\n", -(1LL << (8 * sizeof(int) - 1)));
    printf("%lld\n", (1LL << (8 * sizeof(int) - 1)) - 1);
    
    return 0;
}
