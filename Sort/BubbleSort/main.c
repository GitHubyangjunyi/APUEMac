//
//  main.c
//  BubbleSort
//
//  Created by 杨俊艺 on 2019/8/13.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void BubbleSort(int *a, int n);

int main(int argc, const char * argv[])
{
    int vs[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 04};
    
    BubbleSort(vs, 10);
    
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\t", vs[i]);
    }
    
    
    printf("\n");
    
    
    
    return 0;
}

void BubbleSort(int *a, int n)
{
    int i, j, temp;
    int change = 0;//检测一次排序中是否发生交换,若无交换,则序列有序,仅需一趟排序
    
    for (i = n - 1; i >= 0 && change == 0; i--)//先判断条件再看是否执行
    {
        change = 1;//位置不能变
        
        for (j = 0; j < i; j++)//一次排序
        {
            if (a[j] > a[j + 1])
            {
                change = 0;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

//初始序列
//49 38 65 97 76 13 27 49 55 04
//第一趟
//49 38 65 97 76 13 27 49 55 04     49和38比较 交换
//38 49 65 97 76 13 27 49 55 04     49和65比较

//38 49 65 97 76 13 27 49 55 04     65和97比较
//38 49 65 97 76 13 27 49 55 04     97和76比较 交换

//38 49 65 76 97 13 27 49 55 04     97和13比较 交换
//38 49 65 76 13 97 27 49 55 04     97和27比较 交换

//38 49 65 76 13 27 97 49 55 04     97和49比较 交换
//38 49 65 76 13 27 49 97 55 04     97和55比较 交换

//38 49 65 76 13 27 49 55 97 04     97和04比较 交换
//38 49 65 76 13 27 49 55 04 97     最终97到达序列尾

//进入第二趟,此时最终结束位置为序列尾减去1
