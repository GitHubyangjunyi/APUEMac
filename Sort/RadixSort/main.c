//
//  main.c
//  RadixSort
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define D 10    //桶数10,进制
#define N 9        //排序数9
#define QUEUE_SIZE 128
typedef int datatype;

typedef struct
{
    datatype data[QUEUE_SIZE];
    int front, rear;
}SequentialQueue;

void InitializeSequentialQueue(SequentialQueue *sq);
int EmptySequentialQueue(SequentialQueue *sq);
int GetSequentialQueue(SequentialQueue *sq);
int InsertSequentialQueue(SequentialQueue *sq, datatype x);
int DeleteSequentialQueue(SequentialQueue *sq);

int main(int argc, const char * argv[]) {
    
    int test[N] = { 710,342,45,686,6,429,134,68,24 };
    int i, m = 3;
    RadixSort(test, N, m);
    for ( i = 0; i < N; i++)
    {
        printf("%d\n", test[i]);
    }
    
    
    return 0;
}

void InitializeSequentialQueue(SequentialQueue * sq)
{
    //循环队列初始化: front = rear = QUEUE_SIZE - 1
    //循环队列队头指针进1: front = (front + 1) % QUEUE_SIZE
    //循环队列队尾指针进1: rear = (rear + 1) % QUEUE_SIZE
    //循环队列队满条件: (rear + 1) % QUEUE_SIZE == front
    //循环队列队空条件: front = rear
    sq->front = QUEUE_SIZE - 1;
    sq->rear = QUEUE_SIZE - 1;
}

int EmptySequentialQueue(SequentialQueue * sq)
{
    if (sq->front == sq->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GetSequentialQueue(SequentialQueue * sq)//顺序队列取队头元素,输入队列起始地址,输出队头元素所在位置下标
{
    if (!EmptySequentialQueue(sq))
    {
        return (sq->front + 1) % QUEUE_SIZE;
    }
    else
    {
        return -1;
    }
}

int InsertSequentialQueue(SequentialQueue * sq, datatype x)//顺序队列元素入队,输入队列起始地址,要入队的元素值
{
    if (sq->front == (sq->rear + 1) % QUEUE_SIZE)//队满判断
    {
        return false;
    }
    else
    {
        sq->rear = (sq->rear + 1) % QUEUE_SIZE;//队尾指针后移一位
        sq->data[sq->rear] = x;//x入队
        return true;
    }
}

int DeleteSequentialQueue(SequentialQueue * sq)//顺序队列出队,输入队列起始地址,输出队头元素位置
{
    if (!EmptySequentialQueue(sq))//队非空
    {
        sq->front = (sq->front + 1) % QUEUE_SIZE;//队头指针后移一位
        return sq->front;//返回后移一位后的队头指针
    }
    else//队空
    {
        return -1;
    }
}

void RadixSort(int a[], int n, int m)//基数排序,输入排序数组,排序数目n,排序数的最大位数m
{
    int i, j, k, t;
    SequentialQueue tub[D];//定义D个基数队列
    //初始化D个队列
    for ( i = 0; i < D; i++)
    {
        InitializeSequentialQueue(&tub[i]);
    }
    //进行m次分配和收集
    for ( i = 0; i < m; i++)
    {
        for ( j = 0; j < n; j++)//对n个数字进行处理
        {
            k = (int)(a[j] / pow(D, i)) % D;    //取a[j]中第i位数字,pow用于计算x的y次幂
            InsertSequentialQueue(&tub[k], a[j]);//把a[j]放入第k个队列
        }
        t = 0;
        //在D个队列中收集数字放回a数组中
        for ( j = 0; j < D; j++)
        {
            while (!EmptySequentialQueue(&tub[j]))
            {
                k = DeleteSequentialQueue(&tub[j]);
                a[t] = tub[j].data[k];
                t++;
            }
        }
    }
}

//基数排序是采用分配与收集的方法实现的一种排序方法,又称为桶排序,是通过关键字的部分信息,将要排序的元素分配至某些桶中,以此达到排序的作用

