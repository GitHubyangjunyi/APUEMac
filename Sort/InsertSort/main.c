//
//  main.c
//  InsertSort
//
//  Created by 杨俊艺 on 2019/7/28.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void InsertSort(int *a, int n);

int main(int argc, const char * argv[])
{
    int a[10] = {3, 4, 6, 2, 7, 1 ,8, 0, 9, 5 };
    printf("第一次输出为原始数列:\n");
    for (int i =0; i < 10; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    
    InsertSort(a, 10);
    
    for (int i =0; i < 10; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    
    

    
    
    return 0;
}

void InsertSort(int *a, int n)
{
    int i, j ;
    int temp;//temp作为一个额外的存储空间哨兵
    
    for (i = 1; i < n; ++i)
    {
        if (a[i] < a[i - 1])//如果后面小于前面
        {
            temp = a[i];//哨兵保存后面小的2
            for (j = i - 1; temp < a[j] && j >= 0; --j)//j等于2,此后哨兵temp一直往前比较,如果小于前面的就将前面一个数值往后移动
            {
                a[j + 1] = a[j];//前面的往后面移动为哨兵腾位置
            }
            a[j + 1] = temp;
        }
        for (int i =0; i < 10; i++) {
            printf("%d\t", a[i]);
        }
        printf("\n");
    }
}

//插入排序的基本操作就是将一个数据插入到已经排好序的有序数据中,从而得到一个新的,个数加一的有序数据,由于复杂度较高,所以适用于少量数据的情况下进行排序
//每次从数列中取出一个还没取过的数并按照大小关系插入到已经取出的数中使得取出的数依然有序
//相当于一张一张抽取扑克牌,每次拿到新的扑克牌就将其插入到合适的位置
