//
//  main.c
//  CircleLinkedList
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "CircleLinkedList.h"

int main(int argc, const char * argv[]) {
    
    ElemType a[2] = { 1,2 };
    ElemType b[2] = { 8,9 };
    LinkedListNode *rear;
    LinkedListNode *rearb;
    
    //尾插法建立循环链表
    rear = CreateRearCircleLinkedList(a, 2);
    rearb = CreateRearCircleLinkedList(b, 2);
    
    //将两个循环链表链接成一个
    ConnectTwoCircleLinkedList(rear, rearb);//执行完2 8 9 空 1
    
    return 0;
}
