//
//  main.c
//  SequentialQueue
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    if (sq->front == (sq->rear + 1)% QUEUE_SIZE)//队满判断
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
