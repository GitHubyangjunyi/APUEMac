//
//  main.c
//  ShellSort
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

void shellsort(int v[], int n);

int main(int argc, const char * argv[]) {
    
    
    int vs[9] = { 1,22,3,12,5,63,7,18,0 };
    
    shellsort(vs, 9);
    
    for (size_t i = 0; i < 9; i++)
    {
        printf("%d\t", vs[i]);
    }
    printf("\n");
    
    return 0;
}

void shellsort(int v[], int n)
{
    int gap, i, j, temp;
    
    for (gap = n/2 ; gap > 0; gap /= 2)//最外层的循环控制控制两个被比较元素之间的距离gap,从n/2开始,逐步进行对折,直到为0
        for(i = gap; i < n;i++)//中间的循环用于在元素间移动位置gap每次递增1
            for (j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap)//最内层的循环用于比较各对相距gap个位置的元素,当这两个元素逆序时把它们互换过来
            {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}

//先去看InsertSort直接插入排序
//Shell排序(D.L.Shell于1959年)
//按递增顺序对v[0]...v[n-1]进行排序
//基本思想:
//先比较距离较远的元素,而不是像简单交换排序算法那样先比较相邻的元素,这样可以快速减少大量的无序情况,从而减轻后续工作
//被比较的元素之间的距离逐步减少,直到1,这时候排序变成相邻元素互换
//最外层的循环控制控制两个被比较元素之间的距离,从n/2开始,逐步进行对折,直到为0
//中间的循环用于在元素间移动位置
//最内层的循环用于比较各对相距gap个位置的元素,当这两个元素逆序时把它们互换过来
//由于gap的值最终要递减到1,因此所有元素最终都会位于正确的排序位置上
//
//注意,即使最外层循环的控制变量不是算术级数,for语句的书写形式依然没有变,这就说明for语句有很强的通用性
