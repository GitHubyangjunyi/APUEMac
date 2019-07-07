//
//  main.c
//  LinkStack
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 64
typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}LinkStack;

LinkStack *top;    //栈顶指针

LinkStack *PushLinkStack(LinkStack *top, datatype x);
LinkStack *PopLinkStack(LinkStack *top, datatype *datap);

int main(int argc, const char * argv[]) {
    
    //测试是否有必要返回栈的结构指针
    //也可以不初始化为空而使用下面的两句语句,这样符合栈底的next为NULL的一般约定
    //LinkStack *topPtr;
    //topPtr = PushLinkStack(NULL, 'a');
    LinkStack *topPtr = NULL;
    topPtr = PushLinkStack(topPtr, 'a');
    topPtr = PushLinkStack(topPtr, 'b');
    topPtr = PushLinkStack(topPtr, 'c');
    
    
    
    return 0;
}

LinkStack * PushLinkStack(LinkStack * top, datatype x)
{
    LinkStack *p = (LinkStack *)malloc(sizeof(LinkStack));
    p->data = x;
    p->next = top;
    top = p;
    return top;
}

LinkStack * PopLinkStack(LinkStack * top, datatype * datap)
{
    LinkStack *p;
    if (top != NULL)
    {
        *datap = top->data;
        p = top;
        top = top->next;
        free(p);
    }
    return top;
    //栈空时返回NULL,所以不用对空栈进行特殊处理
}
