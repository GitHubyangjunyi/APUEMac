//
//  main.c
//  Binsearch
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int binsearch(int x, int v[], int n);//x是待查数,v[]是以升序排列的数组,n是数组长度
int binsearchs(int x, int v[], int n);//x是待查数,v[]是以升序排列的数组,n是数组长度

int main(int argc, const char * argv[]) {
    
    int v[7] = { 1,2,3,4,5,6,7 };
    printf("%d\n", binsearch(5, v, 7));
    
    int vs[8] = { 1,2,3,4,5,6,7,8 };
    printf("%d\n", binsearch(5, vs, 8));//没有溢出检测
    
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low = 0;
    int hight = n - 1;
    int mid;
    
    while (low <= hight)
    {
        mid = (low + hight) / 2;
        if (x < v[mid])
            hight = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    
    return -1;
}

int binsearchs(int x, int v[], int n)
{
    int low = 0;
    int hight = n - 1;
    int mid = (low + hight) / 2;
    
    while (low <= hight && x != v[mid])
    {
        if (x < v[mid])
            hight = mid - 1;
        else
            low = mid + 1;
        mid = (low + hight) / 2;
    }
    
    if(x == v[mid])
        return mid;
    else
        return -1;
}

//折半查找(数组v必须以升序排列)
//首先将输入的值x与数组的中间元素比较,如果x小于中间元素的值,则在前半部分查找,否则在后半部分查找
//
//binsearch的while循环内共执行了两次测试,其实只要一次就够了,代价是将更多了测试在循环外执行,重写该函数为binsearchs,使得在循环内部只执行一次测试
//两种方案执行时间几乎没有差异,但binsearchs可读性却变差了
