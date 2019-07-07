//
//  main.c
//  MallocTest
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

LinkedListNode *CreateNode(void);

int main(int argc, const char * argv[]) {
    
    LinkedListNode *head, *x;
    int y;
    
    head = CreateNode();
    
    x = head;
    printf("%p:%d %d\n", x, x->data, x->next);//这三次输出就一样
    printf("%p:%d %d\n", x, x->data, x->next);
    printf("xx\n");
    printf("%p:%d %d\n", x, x->data, x->next);
    
    y = x->data;
    printf("%p:%d %d\n", x, y, x->next);
    
    
    
    return 0;
}

LinkedListNode * CreateNode(void)
{
    LinkedListNode *p, *Heap, Stack;
    
    //Heap指向空间通过malloc函数申请,在堆中分配
    Heap = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    Heap->data = 6;
    Heap->next = NULL;
    
    //Stack变量空间在栈中分配
    Stack = *Heap;//将Heap结点内容复制给Stack结点
    //p = &Stack;
    p = Heap;
    return p;
}

//程序结果一:第40行关闭,41行有效,即返回Heap空间地址时,程序执行结果
//    431fe0:6 0
//    431fe0:6 0
//程序结果二:第40行有效,41行关闭,即返回Stack空间地址时,程序执行结果
//    12ff10:6 0
//    12ff10:1245056 4198561
//
//
//在栈中分配的局部量地址,传递给主函数后,由于局部量空间被系统释放,内容随即消失--将指针值作为函数的返回值时,不要返回一个局部量的地址
//在堆中分配的空间虽然也是子函数局部量,但传递给主函数时,由于这部分空间是由当前运行程序控制的,并未被释放,内容保留
