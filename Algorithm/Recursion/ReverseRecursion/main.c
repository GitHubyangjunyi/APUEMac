//
//  main.c
//  ReverseRecursion
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void reverserecursion(char s[]);
void reverser(char s[], int i, int len);

int main(int argc, const char * argv[]) {
    
    char line[12] = "abcdefghijk";//用来存放字符串
    reverserecursion(line);
    printf("%s\n", line);
    
    
    
    return 0;
}

void reverserecursion(char s[])
{
    void reverser(char s[], int i, int len);
    
    reverser(s, 0, strlen(s));
}

void reverser(char s[], int i, int len)
{
    int c, j;
    
    j = len - (i + 1);//字符串从右端算起的索引
    if (i < j)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverser(s, ++i, len);//每调用一次reverser,字符串从左端算起的索引i就加1
    }
}

//递归版本的reverse函数,将字符串s倒置
//无论在何种实现中,都应保持相同的reverse函数的用接口,因此reverse函数的新版本还是只有一个参数:字符串s
//reverserecursion函数先计算出字符串的长度,然后调用reverser原地倒置字符串s
//reverser函数有3个参数,将被倒置的字符串s,字符串从左端算起的索引i以及字符串的长度len
//i的初值是0,变量j中是字符串从右端算起的索引,通过下列计算得出:
//j = len - (i + 1);
//字符串中的字符是按由外而内的顺序依次进行位置交换的,例如第一组交换位置的两个字符是s[0]和s[len-1],第二组交换的是s[2]和s[len-2]
//每调用一次reverser,字符串从左端算起的索引i就加1
//这一位置交换过程将移之重复到索引i,j指向同一个字符(i == j)或者索引i所指向的字符出现在索引j所指向的字符的右侧(i > j)为止
//此处不适合用递归思想
