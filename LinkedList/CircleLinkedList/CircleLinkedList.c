//
//  CircleLinkedList.c
//  CircleLinkedList
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include "CircleLinkedList.h"
#include <stdlib.h>

LinkedListNode * CreateRearCircleLinkedList(ElemType a[], int n)//尾插法建立循环链表,输入结点值数组,结点个数,输出链表尾指针
{
    LinkedListNode *head, *p, *q;
    int i;
    head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    q = head;
    p = NULL;
    for (i = 0; i < n; i++)
    {
        p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        p->data = a[i];
        q->next = p;
        q = p;
    }
    p->next = head;
    return p;        //返回尾指针
}

void ConnectTwoCircleLinkedList(LinkedListNode * ra, LinkedListNode * rb)//将两个循环链表链接成一个,输入两个循环链表的尾指针
{
    LinkedListNode *p;
    p = ra->next;
    ra->next = rb->next->next;
    free(rb->next);
    rb->next = p;
    //若在单链表或用头指针表示的单循环链表上执行这种链接操作,都需要遍历第一个链表,找到最后的结点,执行时间是O(n)
    //如果采用尾指针表示单循环链表,则只需修改指针而无需遍历,执行时间是O(1)
    
}
