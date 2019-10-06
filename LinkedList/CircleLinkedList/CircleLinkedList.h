//
//  CircleLinkedList.h
//  CircleLinkedList
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#ifndef CircleLinkedList_h
#define CircleLinkedList_h

#include <stdio.h>

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
}LinkedListNode;

LinkedListNode *CreateRearCircleLinkedList(ElemType a[], int n);
void ConnectTwoCircleLinkedList(LinkedListNode *ra, LinkedListNode *rb);

#endif /* CircleLinkedList_h */
