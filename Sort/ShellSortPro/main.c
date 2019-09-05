//
//  main.c
//  ShellSortPro
//
//  Created by 杨俊艺 on 2019/7/28.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void ShellSort(int *arr, int n);
void ShellInsert(int *arr, int n, int dk);

int main(int argc, const char * argv[])
{
    int a[10] = {3, 4, 6, 2, 7, 1 ,8, 0, 9, 5 };
    printf("第一次输出为原始数列:\n");
    for (int i =0; i < 10; i++) {
        printf("%d\t", a[i]);
    }
    
    printf("\n");
    
    ShellSort(a, 10);
    
    for (int i =0; i < 10; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    
    
    
    return 0;
}

void ShellSort(int *arr, int n)
{
    int dlta[3] = {5, 3, 1};
    for (int k = 0; k < 3; k++) {
        ShellInsert(arr, n, dlta[k]);
        printf("完成一次步长得到新序列:\n");
        for (int i =0; i < 10; i++) {
            printf("%d\t", arr[i]);
        }
        printf("\n");
    }
}

void ShellInsert(int *arr, int n, int dk)
{
    int i, j, k, temp;
    for (k = 0; k < dk; k++)//dk是步长
    {
        for (i = k + dk; i < n; i = i + dk)
        {
            if (arr[i] < arr[i - dk])//插入数据小于前面一个数据
            {
                temp = arr[i];//存储插入的数据
                for (j = i - dk; temp < arr[j] && j >= 0; j = j - dk)//移位直到找到插入数据的顺序位置
                {
                    arr[j + dk] = arr[j];//前面的往后面移动为哨兵腾位置
                }
                arr[j + dk] = temp;
            }
            printf("执行一次两两比较并按需交换位置(%d)\t(%d)\n", i - dk, i);
            for (int i =0; i < 10; i++) {
                printf("%d\t", arr[i]);
            }
            printf("\n");
        }
    }
    printf("一次步长结束,进入下一次步长\n");
}

//希尔排序基于直接插入排序,先看InsertSort项目
