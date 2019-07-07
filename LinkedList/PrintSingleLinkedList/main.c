//
//  main.c
//  PrintSingleLinkedList
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 6        //链表结点数

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
}LinkedListNode;

LinkedListNode *CreateRearLinkedList(ElemType a[], int n);
void PrintSingleLinkedList(LinkedListNode *L);
void PrintSingleLinkedListRecursion(LinkedListNode *L);

int main(int argc, const char * argv[]) {
    
    
    LinkedListNode *L;
    ElemType list[N] = { 1,2,3,4,5,6 };
    
    L = CreateRearLinkedList(list, N);
    PrintSingleLinkedList(L);
    
    printf("使用递归版本\n");
    PrintSingleLinkedListRecursion(L);
    char GETCHAR = getchar();
    return 0;
}

LinkedListNode * CreateRearLinkedList(ElemType a[], int n)//尾插法建立链表,输入结点值数组,结点个数,输出链表头指针
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
    p->next = NULL;
    return head;
}

void PrintSingleLinkedList(LinkedListNode * L)
{
    LinkedListNode *p;
    int array[N];
    int i = N - 1;//5
    p = L->next;//跳过头结点
    while (p)//链表非空
    {
        array[i--] = p->data;//链表结点值从数组的最后往前顺序存放
        p = p->next;
    }
    while (i+++1 < N)//while (i++ < N)
    {
        printf("%d\n", array[i]);
    }
}

void PrintSingleLinkedListRecursion(LinkedListNode * L)//递归实现逆序
{
    if (L->next != NULL)
    {
        PrintSingleLinkedListRecursion(L->next);
    }
    printf("%d\n", L->data);
}
