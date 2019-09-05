//
//  main.c
//  QuickSort
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void quicksort(int v[], int left, int right);
void swap(int v[], int i, int j);

int main(int argc, const char * argv[])
{
    
    int vs[9] = { 1, 22, 3, 12, 5, 63, 7, 18, 0};
    
    quicksort(vs, 0, 8);
    
    for (size_t i = 0; i < 9; i++)
    {
        printf("%d\t", vs[i]);
    }
    
    printf("\n");
    
    return 0;
}

void quicksort(int v[], int left, int right)//以递增顺序对v[left]...v[right]进行排序
{
    int i, last;
    void swap(int v[], int i, int j);
    
    if (left >= right)//若数组包含的元素少于2个,则不执行任何操作
        return;
    swap(v, left, (left + right) / 2);//将划分子集的元素移动到v[0]
    last = left;
    
    for (i = left + 1; i <= right; i++)//划分子集
        if (v[i] < v[left])
            swap(v, ++last, i);
    
    swap(v, left, last);//恢复划分子集的元素
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}

void swap(int v[], int i, int j)//交换v[i]和v[j]的值
{
    int temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//快速排序是对冒泡排序的一种改进,分治与递归的思想
//
//快速排序(C.A.R.Hoare于1962年)
//标准库提供了一个qsort函数,可对任何类型的对象进行排序
//对于一个给定的数组,从中选择一个元素,以该元素为界将其余元素划分为两个子集,一个子集中的所有元素都小于该元素,另一个子集中的所有元素都大于或等于该元素
//对这样两个子集递归执行这一过程,当某个子集中的元素数小于2时,这个子集就不需要再次排序,终止递归
//从执行速度来讲,这个版本的快速排序可能不是最快的,但它是最简单的算法之一,每次划分子集时,该算法总是选取各个子数组的中间元素

//可以Bilibili搜索快速排序,选择Ted的那个版本进行查看

//原始序列
//1 22 3 12 5 63 7 18 0
//划分子集的元素移动到v[0]
//5 22 3 12 1 63 7 18 0
//划分子集
//  第一次不变5 22 3 12 1 63 7 18 0
//  第二次   5 3 22 12 1 63 7 18 0
//  第三次不变5 3 22 12 1 63 7 18 0
//  第四次交换5 3 1 12 22 63 7 18 0
//  第五次
//  第六次
//  第七次
//  第八次交换5 3 1 0 22 63 7 18 12
//恢复划分子集元素
//0 3 1 5 22 63 7 18 12
//最后递归排序两个部分
//从0到元素值5之前的一部分
//从元素值5之后的一部分
