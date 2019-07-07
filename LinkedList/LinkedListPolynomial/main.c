//
//  main.c
//  LinkedListPolynomial
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Polynode
{
    int coef;//系数
    int exp;//指数
    struct Polynode *next;
}LinkedListNode;

LinkedListNode *CreateListRear(ElemType a[][2], int n);
LinkedListNode *PolyAddHeadC(LinkedListNode *headA, LinkedListNode *headB);
LinkedListNode *Attach(ElemType c, int e, LinkedListNode *pc);
void *PolyAddHeadA(LinkedListNode *polyA, LinkedListNode *polyB);

int main(int argc, const char * argv[]) {

    int a[][2] = { {3,14},{2,8},{1,6} };
    int b[][2] = { {8,14},{-3,10},{10,6},{1,0} };
    LinkedListNode *headA, *headB, *linkPtr;
    
    headA = CreateListRear(a, 3);
    headB = CreateListRear(b, 4);
    linkPtr = PolyAddHeadC(headA, headB);
    PolyAddHeadA(headA, headB);
    
    
    
    return 0;
}

LinkedListNode * CreateListRear(ElemType a[][2], int n)//尾插法建立一元多项式链表,输入多项式系数与指数数组地址,多项式项数,输出多项式链表首地址
{
    LinkedListNode *head, *p, *q;
    int i;
    p = NULL;
    q = head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    for (i = 0; i < n; i++)
    {
        p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        p->coef = a[i][0];
        p->exp = a[i][1];
        
        q->next = p;
        q = p;
    }
    p->next = NULL;
    return head;
}

LinkedListNode * PolyAddHeadC(LinkedListNode * headA, LinkedListNode * headB)//将两个多项式polyA和polyB相加,结果存放在polyC中,输入polyA和polyB链表首地址,输出polyC链表地址
{
    LinkedListNode *headC, *pa, *pb, *pc, *p;
    ElemType x;
    
    pa = headA->next;
    pb = headB->next;
    headC = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    pc = headC;
    while (pa && pb)//都是非空结点,都未处理完
    {
        if (pa->exp == pb->exp)
        {
            x = pa->coef + pb->coef;
            if (x != 0)//系数和非0,在C链表中添加新结点
            {
                pc = Attach(x, pa->exp, pc);
            }
            pa = pa->next;//两个指针后移继续循环
            pb = pb->next;
            continue;
        }
        if (pa->exp < pb->exp)
        {
            p = pa;
            pa = pa->next;
        }
        else
        {
            p = pb;
            pb = pb->next;
        }
        pc = Attach(p->coef, p->exp, pc);
    }
    //p指向未处理完的链
    p = pa;//先令p指向pa,若pa为空则表示pa链已经处理完,令p指向pb链
    if (pa == NULL)
    {
        p = pb;
    }
    while (p)//将未处理完的链表的剩余部分添加到新链表上
    {
        pc = Attach(p->coef, p->exp, pc);
        p = p->next;
    }
    pc->next = NULL;//新链表最后一项NULL
    return headC;
}

LinkedListNode * Attach(ElemType c, int e, LinkedListNode * pc)//建立系数为c,指数为e的新结点,将其插在pc所指向的结点的后面,链接后pc指向新链入的结点
{
    LinkedListNode *p = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    p->coef = c;
    p->exp = e;
    pc->next = p;
    return p;
}

void * PolyAddHeadA(LinkedListNode * polyA, LinkedListNode * polyB)//将两个多项式polyA和polyB相加,结果存放在polyA中,并将多项式polyB删除,输入polyA和polyB链表首地址
{
    LinkedListNode *pa, *pb, *pre, *temp;
    int sum;
    //令pa和pb分别指向多项式的链表的第一个结点
    pa = polyA->next;
    pb = polyB->next;
    pre = polyA;//pre指向和多项式尾结点
    while (pa != NULL && pb != NULL)//都未扫描完成
    {
        if (pa->exp == pb->exp)//若指数相等
        {
            sum = pa->coef + pb->coef;//相应的系数相加
            if (sum != 0)//若系数和不为0
            {
                pa->coef = sum;
                pre->next = pa;
                pre = pre->next;
                pa = pa->next;
                temp = pb;
                pb = pb->next;
                free(temp);
                continue;
            }
            else//若系数和为0
            {
                temp = pa->next;
                free(pa);
                pa = temp;
                temp = pb->next;
                free(pb);
                pb = temp;
                continue;
            }
        }
        if (pa->exp < pb->exp)//pa指数小于pb指数,pa和pre指针后移
        {
            pre->next = pa;
            pre = pre->next;
            pa = pa->next;
            continue;
        }
        if (pa->exp > pb->exp)//pa指数大于pb指数,将pb结点加入到pa之前
        {
            pre->next = pb;
            pre = pre->next;
            pb = pb->next;
            pre->next = pa;
            continue;
        }
    }
    if (pb != NULL)//将剩余的pb加入到和多项式中
    {
        pre->next = pb;
    }
}
