//
//  main.c
//  SequentialList
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define LIST_SIZE 1024    //线性表的最大长度1024
typedef int ElemType;    //线性表元素的类型为整型
typedef struct
{
    ElemType data[LIST_SIZE];
    int last;            //指向最后节点的位置
}SequenList;

SequenList *LPtr;        //指向SequenList结构的指针

void ErgodicSequenList(SequenList *LPtr);//遍历
int InsertSequenList(SequenList *LPtr, ElemType x, int k);
int DeleteSequenList(SequenList *LPtr, int k);
int LocateSequenList(SequenList *LPtr, ElemType key);
int GetSequenList(SequenList *LPtr, int i, ElemType *e);

int main(int argc, const char * argv[]) {
    
    
    printf("sizeof(SequenList) = %d\n", sizeof(SequenList));//4100 = 4 * 1024 + 4
    SequenList sl;
    sl.data[0] = 1;
    sl.last = 0;
    LPtr = &sl;
    DeleteSequenList(LPtr, 0);//删除失败
    ErgodicSequenList(LPtr);
    InsertSequenList(LPtr, 2, 1);
    //DeleteSequenList(LPtr, 0);
    //ErgodicSequenList(LPtr);
    //InsertSequenList(LPtr, 3, 3);
    //InsertSequenList(LPtr, 4, 5);//位置非法,不予插入,比如只有三个元素,却要插入到第六位置
    //ErgodicSequenList(LPtr);
    LocateSequenList(LPtr, 2);
    
    
    return 0;
}

void ErgodicSequenList(SequenList * LPtr)
{
    printf("开始遍历顺序表:\n");
    
    for (int i = 0; i <= LPtr->last; i++)
    {
        printf("第%d个元素data[%d] = %d\n", i + 1, i, LPtr->data[i]);
    }
}

int InsertSequenList(SequenList * LPtr, ElemType x, int k)
{
    int j;
    if (LPtr->last == LIST_SIZE - 1)
    {
        printf("插入失败!顺序表已满!\n");
        return FALSE;
    }
    else if (k < 0 || k > (LPtr->last + 1))
    {
        printf("插入失败!位置非法!\n");
        return FALSE;
    }
    else
    {
        for (  j = LPtr->last; j >=k; j--)//从顺序表最后一个元素开始移动数据
        {
            LPtr->data[j + 1] = LPtr->data[j];
        }
        LPtr->data[k] = x;//将x放入节点k
        LPtr->last = LPtr->last + 1;//修改最后节点指针
    }
    printf("插入成功!插入值为%d,是顺序表第%d个元素date[%d]\n", LPtr->data[k], LPtr->last + 1,LPtr->last);
    return TRUE;
}

int DeleteSequenList(SequenList * LPtr, int k)
{
    if ((k >= 0 && k <= LPtr->last) && (LPtr->last != 0))//删除成功要减去下标值,所以不能为0
    {
        for (int j = k; j <= LPtr->last; j++)
        {
            LPtr->data[j] = LPtr->data[j + 1];
        }
        LPtr->last--;
        printf("删除成功!\n");
        return TRUE;
    }
    printf("删除失败!\n");
    return FALSE;
}

int LocateSequenList(SequenList * LPtr, ElemType key)
{
    for (int i = 0; i <= LPtr->last; i++)
    {
        if (LPtr->data[i] == key)
        {
            printf("找到!\n");
            return i;
        }
    }
    printf("未找到!\n");
    return -1;
}

int GetSequenList(SequenList * LPtr, int i, ElemType * e)
{
    if (i < 0 || i >LPtr->last)
    {
        return FALSE;
    }
    if (LPtr->last < 0)
    {
        return FALSE;
    }
    *e = LPtr->data[i];
    return TRUE;
}
