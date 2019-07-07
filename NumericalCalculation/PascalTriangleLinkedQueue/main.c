//
//  main.c
//  PascalTriangleLinkedQueue
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 188
#define QUEUE_SIZE 128
typedef int datatype;

typedef struct node    //链结点的数据类型
{
    datatype data;
    struct node *next;
}LinkedListNode;

typedef struct  //链中头尾指针的数据类型
{
    LinkedListNode *front, *rear;
}LinkedQueue;

LinkedQueue *lq;

void InitializeLinkedQueue(LinkedQueue *lq);
int EmptyLinkedQueue(LinkedQueue *lq);
int GetLinkedQueue(LinkedQueue *lq, datatype *x);
void InsertLinkedQueue(LinkedQueue *lq, datatype x);
LinkedListNode *DeleteLinkedQueue(LinkedQueue *lq);
void DestoryLinkedQueue(LinkedQueue *lq);

int main(int argc, const char * argv[]) {
    
    LinkedQueue node;
    LinkedQueue *lqPtr = &node;
    LinkedListNode *sPtr;
    datatype value;
    
    InitializeLinkedQueue(lqPtr);
    InsertLinkedQueue(lqPtr, 0);
    InsertLinkedQueue(lqPtr, 1);
    InsertLinkedQueue(lqPtr, 1);
    InsertLinkedQueue(lqPtr, 0);
    
    for (int i = 0; i < N; i++)
    {
        sPtr = DeleteLinkedQueue(lqPtr);//队头元素出队
        if (sPtr != NULL)
        {
            value = sPtr->data + lqPtr->front->next->data;//队头两个元素求和生成新的系数
            if (sPtr->data != 0)
            {
                printf("%d ", sPtr->data);
            }
            InsertLinkedQueue(lqPtr, value);//新系数入队
        }
        if (lqPtr->front->next->data == 0)//队头元素为分隔符
        {
            InsertLinkedQueue(lqPtr, 0);//分隔符入队
            printf("\n");
        }
    }
    
    char GETCHAR = getchar();
    return 0;
}

void InitializeLinkedQueue(LinkedQueue * lq)
{
    lq->front = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    lq->front->next = NULL;
    lq->rear = lq->front;
}

int EmptyLinkedQueue(LinkedQueue * lq)
{
    if (lq->front == lq->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GetLinkedQueue(LinkedQueue * lq, datatype * x)//链队列取队头结点值,输入链队列起始地址,要接收值的指针,输出成功或失败标志
{
    if (EmptyLinkedQueue(lq))
    {
        return false;
    }
    else
    {
        x = &(lq->front->next->data);
        return true;
    }
}

void InsertLinkedQueue(LinkedQueue * lq, datatype x)
{
    lq->rear->next = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    lq->rear = lq->rear->next;//修改队列尾指针
    lq->rear->data = x;          //新结点赋值
    lq->rear->next = NULL;      //尾结点指针域置NULL
}

LinkedListNode *DeleteLinkedQueue(LinkedQueue * lq)//链队列出队,输入队列起始地址,输出队列头结点地址
{
    LinkedListNode *s;
    if (!EmptyLinkedQueue(lq))//队列非空
    {
        s = lq->front->next;//s指向队列头结点
        if (s->next == NULL)//队列中只有一个结点
        {
            lq->rear = lq->front;//队列置空
        }
        else
        {
            lq->front->next = s->next;//摘下队列头结点
            return s;//返回摘下的队列头结点地址
        }
    }
    return NULL;//队列为空返回NULL
}

void DestoryLinkedQueue(LinkedQueue * lq)//销毁链队列,输入队列起始地址
{
    LinkedListNode *s;
    while (!EmptyLinkedQueue(lq))
    {
        s = DeleteLinkedQueue(lq);
        free(s);
    }
    free(lq->front);
    lq->front = NULL;
    lq->rear = NULL;
}

//链队列由单链表构成,头指针front指向头结点,尾指针rear指向尾结点,头尾指针组合在一个结构中,队列指针lq指向此结构
//使用循环队列构造杨辉三角时,由于有队满的限制,不得不面临数组可能溢出的问题,结果的规模会相应受限
//这里使用链队列实现杨辉三角
