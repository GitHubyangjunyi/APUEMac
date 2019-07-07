//
//  main.c
//  MINEOSListTest
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node//这样定义的结点(只有前后链接点而没有数据)是因为在任务状态段TSS中只需要一个位域去链接不同的TSS形成任务链表,MINEOS不使用任务门进行任务切换
{
    struct node * prev;
    struct node * next;
}List;

//使用这种定义将会出现错误:不允许指针指向不完整的类类型,不完整类型应该是GNU C扩展
//typedef struct
//{
//    struct List * prev;
//    struct List * next;
//}List;

inline void list_init(List * list);
inline void list_add_to_behind(List * entry, List * new);
inline void list_add_to_before(List * entry, List * new);
inline void list_del(List * entry);
inline long list_is_empty(List * entry);
inline struct List * list_prev(List * entry);
inline struct List * list_next(List * entry);

int main(int argc, const char * argv[]) {
    

    List list;
    List *listPtr = &list;
    list_init(listPtr);
    
    List newlist;
    List *newlistPtr = &newlist;
    list_init(listPtr);
    
    list_add_to_behind(listPtr, newlistPtr);
    
    
    
    return 0;
}

inline void list_init(List * list)//初始化list,前驱和后继都指向自己
{
    list->prev = list;
    list->next = list;
}

inline void list_add_to_behind(List * entry, List * new)//
{
    new->next = entry->next;
    new->prev = entry;
    new->next->prev = new;
    entry->next = new;
}

inline void list_add_to_before(List * entry, List * new)
{
    new->next = entry;
    entry->prev->next = new;
    new->prev = entry->prev;
    entry->prev = new;
}

inline void list_del(List * entry)//删除一个指定结点
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

inline long list_is_empty(List * entry)//双向链表是不是为空
{
    if (entry == entry->next && entry->prev == entry)//为空返回1
        return 1;
    else
        return 0;
}

inline struct List * list_prev(List * entry)//不加struct报错???
{
    if (entry->prev != NULL)
        return entry->prev;
    else
        return NULL;
}

inline struct List * list_next(List * entry)//不加struct报错???
{
    if (entry->next != NULL)
        return entry->next;
    else
        return NULL;
}
