//
//  main.c
//  QuickSortTwo
//
//  Created by 杨俊艺 on 2019/8/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void QuickSort(int *arr, int n);
void QSort(int *arr, int n, int low, int high);
int Partition(int arr[], int low, int high);

int main(int argc, const char * argv[])
{
    int vs[9] = { 1, 22, 3, 12, 5, 63, 7, 18, 0};
    
    QuickSort(vs, 9);
    
    for (size_t i = 0; i < 9; i++)
    {
        printf("%d\t", vs[i]);
    }
    
    printf("\n");
    
    return 0;
}

void QuickSort(int *arr, int n)
{
    QSort(arr, n, 0, n - 1);
}


void QSort(int *arr, int n, int low, int high)
{
    int pivotloc;//枢轴
    
    if (low < high)
    {
        pivotloc = Partition(arr, low, high);
        QSort(arr, n, low, pivotloc - 1);
        QSort(arr, n, pivotloc + 1, high);
    }
}

int Partition(int arr[], int low, int high)
{
    int pivotloc = arr[low], temp;//以第一个元素为枢轴
    
    //前后两路查找
    while (low < high)
    {
        while (low < high && arr[high] >= pivotloc)
        {
            --high;
        }
        temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
        
        while (low < high && arr[low] <= pivotloc)
        {
            ++low;
        }
        temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
    return low;
}
