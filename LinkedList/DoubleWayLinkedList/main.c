//
//  main.c
//  DoubleWayLinkedList
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *prior, *next;
}DoubleWayLinkedListNode;

void InsertBeforeDoubleWayLinkedList(DoubleWayLinkedListNode *p, ElemType x);
DoubleWayLinkedListNode *GetDoubleWayLinkedListNode(DoubleWayLinkedListNode *head, int index);
DoubleWayLinkedListNode *DeleteDoubleWayLinkedListNode(DoubleWayLinkedListNode *Ptr);
DoubleWayLinkedListNode *DeleteIndexDoubleWayLinkedListNode(DoubleWayLinkedListNode *head, int index);

int main(int argc, const char * argv[]) {
    
    
    DoubleWayLinkedListNode x;//申请的第一个结点
    DoubleWayLinkedListNode *head;//头结点
    DoubleWayLinkedListNode *p;//中间结点
    DoubleWayLinkedListNode *Ptr;//要删除的结点
    
    p = &x;
    p->data = 6;
    p->prior = p->next = NULL;
    
    InsertBeforeDoubleWayLinkedList(p, -1);
    head = p->prior;
    InsertBeforeDoubleWayLinkedList(p, 1);
    InsertBeforeDoubleWayLinkedList(p, 2);
    InsertBeforeDoubleWayLinkedList(p, 3);
    InsertBeforeDoubleWayLinkedList(p, 4);
    
    Ptr = p->prior;
    InsertBeforeDoubleWayLinkedList(p, 5);
    
    //在双向链表中删除第i个结点
    printf("删除第3个结点值为: %d\n", DeleteIndexDoubleWayLinkedListNode(head, 3)->data);
    
    //在双向链表中删除指定结点
    printf("删除指定结点值为: %d\n", DeleteDoubleWayLinkedListNode(Ptr)->data);
    
    
    
    return 0;
}

void InsertBeforeDoubleWayLinkedList(DoubleWayLinkedListNode * p, ElemType x)//在指定结点前插入,输入指定结点地址,要插入的值
{
    //确保传入的结点地址无异常
    DoubleWayLinkedListNode *s;
    s = (DoubleWayLinkedListNode*)malloc(sizeof(DoubleWayLinkedListNode));
    s->data = x;
    
    s->prior = p->prior;
    
    if (p->prior != NULL)
    {
        p->prior->next = s;
    }
    s->next = p;
    p->prior = s;
    //时间复杂度O(1)
}

DoubleWayLinkedListNode * GetDoubleWayLinkedListNode(DoubleWayLinkedListNode * head, int index)//找到第i个结点的地址(跳过头结点),输入双链表首地址,待查找编号index,输出i结点地址
{
    int j = 1;
    DoubleWayLinkedListNode *Ptr;
    Ptr = head->next;
    while (j++ < index)
    {
        Ptr = Ptr->next;
    }
    return Ptr;
}

DoubleWayLinkedListNode * DeleteDoubleWayLinkedListNode(DoubleWayLinkedListNode * Ptr)//删除双向链表指定的结点,输入待删除结点地址,输出被删除结点地址
{
    //确保传入的结点地址无异常
    Ptr->prior->next = Ptr->next;
    Ptr->next->prior = Ptr->prior;
    return Ptr;
    //结点仅脱链,空间未释放
    //时间复杂度O(1)
}

DoubleWayLinkedListNode * DeleteIndexDoubleWayLinkedListNode(DoubleWayLinkedListNode * head, int index)//删除双向链表的i结点,输入双向链表头结点,待删除结点编号,输出被删除结点地址
{
    DoubleWayLinkedListNode *Ptr;
    Ptr = GetDoubleWayLinkedListNode(head, index);//找到index结点地址
    if (Ptr != NULL)
    {
        Ptr = DeleteDoubleWayLinkedListNode(Ptr);//删除index结点
    }
    return Ptr;
}

