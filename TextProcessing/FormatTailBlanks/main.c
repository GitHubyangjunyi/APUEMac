//
//  main.c
//  FormatTailBlanks
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int removes(char s[]);

int main(int argc, const char * argv[]) {
   
    char line[MAXLINE];
    
    while (getline(line, MAXLINE) > 0)
    {
        if (removes(line) > 0)//如果长度大于0,则说明line中有不是空格或制表符的其他字符,则显示出来
            printf("%s", line);//如果小于0,则这一行完全是由空白符组成的,忽略不显示
    }
    
    
    
    return 0;
}

int getline(char s[], int lim)
{
    int c, i, j;
    
    j = 0;//用来记录被复制到字符串s中的字符个数
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim - 2)//给换行符和字符串结束符留位置
        {
            s[j] = c;
            ++j;
        }
    if (c == '\n')//读到换行符
    {
        s[j] = c;//将换行符写入倒数第二个位置
        ++j;
        ++i;
    }
    s[j] = '\0';//把字符'\0'(空字符,值为0)插入到创建的数组的末尾,以标记字符串的结束
    return i;//返回字符串长度
}

int removes(char s[])//removes函数负责删掉字符串line末尾的空格和制表符并返回新长度
{
    int i = 0;
    
    while (s[i] != '\n')//1.首先找到换行符,然后倒退一个位置
    {
        ++i;
    }
    --i;
    
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))//2.从后向前检查空格或制表符,直到找到一个不是空格或制表符的字符或者没有字符可以继续倒退(i<0)
        --i;
    
    if (i >= 0)//3.将换行符和字符串结束符写回输入行
    {
        ++i;
        s[i] = '\n';
        ++i;
        s[i] = '\0';
    }
    
    return i;//4.返回变量i
}

//删除每个输入行末尾的空格及制表符,并删除完全是空格的行(注意,是末尾,跟SpaceSubstitution不一样)
//注意,输入的一行必须要以换行符作为结束,不然引发异常
