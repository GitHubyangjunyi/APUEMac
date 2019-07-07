//
//  main.c
//  FrequencyHistogram
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

#define MAXHIST 15    //直方图的最大长度
#define MAXCHAR 128 //最大不同字符数量

int main(int argc, const char * argv[]) {
    
    int c, i;
    int len;
    int maxvalue;
    int cc[MAXCHAR];//1.用来存储不同字符的出现次数
    
    for (i = 0; i < MAXCHAR; ++i)
        cc[i] = 0;//2.先将数组全部置0
    
    while ((c = getchar()) != EOF)//3.每读取一个字符,得到该字符对应的ASCII码后写入该ASCII码所对应下标的数组单元
    {
        if (c < MAXCHAR)        //限制:该字符必须在128范围内
            ++cc[c];
    }
    //4.至此,对各个字符出现次数已经统计完毕
    maxvalue = 0;
    for (i = 1; i < MAXCHAR; ++i)//5.找出出现次数最多的字符的出现次数,课后答案的初始状态设置i=1,ASCII为0的字符输不进去
    {
        if (cc[i] > maxvalue)
            maxvalue = cc[i];
    }
    
    for (i = 1; i < MAXCHAR; ++i)//6.开始逐个打印,课后答案的初始状态设置i=1,ASCII为0的字符输不进去
    {
        if (isprint(i))//用这个宏来判断某个字符是不是一个可显示字符
            printf("%5d - %c - %5d : ", i, i, cc[i]);
        else
            printf("%5d -    - %5d : ", i, cc[i]);
        if (cc[i] > 0)//字符至少有出现过一次的
        {
            if ((len = cc[i] * MAXHIST / maxvalue) <= 0)//最大值为比例1,其他为最大值的几分之几,MAXHIST * cc[i] / maxvalue
                len = 1;        //len求值并判断
        }
        else//字符从未出现过的
            len = 0;
        
        while (len > 0)
        {
            putchar('*');
            --len;
        }
        putchar('\n');
    }
    
    
    return 0;
}

//频度直方图:打印输入中各个字符出现频度的直方图,频度是相对于最大出现次数的几分之几
//统计各个字符的出现频度,使用了一个元素个数等于MAXCHAR的字符计数器数组
//如果使用的字符集中存在值大于或等于MAXCHAR的字符,则这些字符将被忽略
//并且使用了一个宏来判断某个字符是不是一个可显示字符
