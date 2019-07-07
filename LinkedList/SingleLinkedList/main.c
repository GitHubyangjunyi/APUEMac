//
//  main.c
//  SingleLinkedList
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
    struct node *next;
}LinkedListNode;

LinkedListNode *InitializeLinkedList(void);
LinkedListNode *CreateRearLinkedList(ElemType a[], int n);
LinkedListNode *CreateFrontLinkedListOne(ElemType a[], int n);
LinkedListNode *CreateFrontLinkedListTwo(ElemType a[], int n);
LinkedListNode *CreateFrontLinkedListThree(ElemType a[], int n);
LinkedListNode *LocateLinkedListValue(LinkedListNode *head, ElemType key);
LinkedListNode *LocateLinkedListIndex(LinkedListNode *head, int index);
void InsertLinkedListAfter(LinkedListNode *Ptr, ElemType value);
void InsertLinkedListBefore(LinkedListNode *head, LinkedListNode *Ptr, ElemType value);
LinkedListNode *DeleteAfterLinkedList(LinkedListNode *Ptr);
LinkedListNode *DeleteIndexLinkedList(LinkedListNode *head, int index);

int main(int argc, const char * argv[]) {
    
    ElemType a[5] = { 1,2,3,4,5 };
    LinkedListNode *head;
    
    //尾插法建立单链表
    head = CreateRearLinkedList(a, 5);
    
    //头插法建立单链表一
    head = CreateFrontLinkedListOne(a, 5);
    
    //头插法建立单链表二
    head = CreateFrontLinkedListTwo(a, 5);
    
    //头插法建立单链表三
    head = CreateFrontLinkedListThree(a, 5);
    
    //按值查找链表结点
    printf("%d\n", LocateLinkedListValue(head, 4)->data);
    
    //按序号查找链表结点
    printf("%d\n", LocateLinkedListIndex(head, 3)->data);
    
    //指定位置后插入结点
    InsertLinkedListAfter(LocateLinkedListIndex(head, 3), 33);
    
    //指定位置前插入结点
    InsertLinkedListBefore(head, LocateLinkedListIndex(head, 3), 11);
    
    //删除指定结点的后继结点
    printf("删除指定结点的后继结点: %d\n", (DeleteAfterLinkedList(LocateLinkedListIndex(head, 3)))->data);//这里第三个元素不是3了,是11
    
    
    LinkedListNode *wantfree = DeleteAfterLinkedList(LocateLinkedListIndex(head, 3));
    printf("未释放之前的值: %d\n", wantfree->data);
    free(wantfree);
    printf("释放之后的值: %d\n", wantfree->data);//此时的值就无效了
    
    //删除第i个结点(正常)
    LinkedListNode *wantfrees = DeleteIndexLinkedList(head, 5);
    printf("未释放之前的值: %d\n", wantfrees->data);
    free(wantfrees);
    printf("释放之后的值: %d\n", wantfrees->data);//此时的值就无效了
    
    //删除第i个结点(异常)
    //LinkedListNode *wantfreex = DeleteIndexLinkedList(head, 5);//返回NULL
    //printf("未释放之前的值: %d\n", wantfreex->data);//NULL不可读取
    //free(wantfreex);
    //printf("释放之后的值: %d\n", wantfreex->data);
    
    
    return 0;
}

LinkedListNode * InitializeLinkedList(void)//初始化单链表,输出链表头指针
{
    LinkedListNode *head;
    head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (head==NULL)//存储空间分配失败
    {
        exit(1);
    }
    head->next = NULL;
    return head;
    //一般C语言书上建议不要返回局部量的地址,这个函数设计是否可靠要进行测试,测试用例见MallocTest/MallocTestTwo
}

LinkedListNode * CreateRearLinkedList(ElemType a[], int n)//尾插法建立链表,输入结点值数组,结点个数,输出链表头指针
{
    LinkedListNode *head, *p, *q;
    int i;
    head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    q = head;
    p = NULL;
    for ( i = 0; i < n; i++)
    {
        p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        p->data = a[i];
        q->next = p;
        q = p;
    }
    p->next = NULL;
    return head;
}

LinkedListNode * CreateFrontLinkedListOne(ElemType a[], int n)//头插法建立链表,输入结点值数组,结点个数,输出链表头指针
{
    LinkedListNode *head, *p, *q;
    int i;
    head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    head->next = NULL;
    q = head->next;
    for ( i = n - 1; i >= 0; i--)
    {
        p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        p->data = a[i];
        p->next = q;
        head->next = p;
        q = head->next;
    }
    return head;
}

LinkedListNode * CreateFrontLinkedListTwo(ElemType a[], int n)
{
    LinkedListNode *head, *p, *q;
    int i;
    q = NULL;
    for (i = n - 1; i >= 0; i--)
    {
        p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        p->data = a[i];
        p->next = q;
        q = p;
    }
    head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    head->next = q;
    return head;
}

LinkedListNode * CreateFrontLinkedListThree(ElemType a[], int n)
{
    LinkedListNode *head, *p;
    int i;
    head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    head->next = NULL;
    for (i = n - 1; i >= 0; i--)
    {
        p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        p->data = a[i];
        p->next = head->next;
        head->next = p;
    }
    return head;
}

LinkedListNode * LocateLinkedListValue(LinkedListNode * head, ElemType key)//按值查找链表结点,输入链表头指针,结点值,输出结点指针(头结点index=0)
{
    LinkedListNode *p;
    p = head->next;//跳过表头结点
    while (p != NULL && p->data != key)
    {
        p = p->next;
    }
    return p;
}

LinkedListNode * LocateLinkedListIndex(LinkedListNode * head, int index)//按序号查找单链表结点,输入链表头指针,序号,输出结点指针(头结点index=0)
{
    LinkedListNode *p = head;
    int j = 0;
    if (index == 0)//头结点index=0
    {
        return NULL;
    }
    while (j < index && p->next != NULL)
    {
        p = p->next;
        j++;
    }
    if (index == j)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

void InsertLinkedListAfter(LinkedListNode * Ptr, ElemType value)//指定位置后插入结点,输入插入点地址,结点值
{
    LinkedListNode *s;
    s = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    s->data = value;
    s->next = Ptr->next;
    Ptr->next = s;
}

void InsertLinkedListBefore(LinkedListNode * head, LinkedListNode * Ptr, ElemType value)//指定位置前插入结点,输入链表头指针,插入点地址,结点值
{
    LinkedListNode *s, *qPtr;
    s = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    s->data = value;
    qPtr = head;
    while (qPtr->next != Ptr)//查找Ptr前驱结点
    {
        qPtr = qPtr->next;
    }
    s->next = Ptr;
    qPtr->next = s;
}

LinkedListNode * DeleteAfterLinkedList(LinkedListNode * Ptr)//删除指定结点的后继结点,输入指定结点地址,输出被删除结点地址(头结点index=0)
{
    LinkedListNode *fPtr;//用来保存被删除结点
    fPtr = Ptr->next;
    Ptr->next = fPtr->next;
    return fPtr;
    //被删除的结点所占用的空间是未释放的,主要是考虑到调用者后续可能要使用这个被删除的结点,所以结点的释放时机由调用者决定
    //但被删除的结点一旦不再使用,就要释放防止内存泄漏
}

LinkedListNode * DeleteIndexLinkedList(LinkedListNode * head, int index)//删除第i个结点,输入链表头指针,结点序号,输出被删除结点地址(头结点index=0)
{
    LinkedListNode *Ptr, *qPtr = NULL;
    Ptr = LocateLinkedListIndex(head, index - 1);//找到index结点的前驱结点
    if (Ptr != NULL && Ptr->next != NULL)//要删除的结点有无异常由这里进行处理,这个结点不是空结点,并且这个结点的后继结点也不是空结点
    {
        qPtr = DeleteAfterLinkedList(Ptr);//结点无异常则删除
    }
    return qPtr;
    //时间复杂度O(n),耗费在查找操作
}
