//
//  main.c
//  PointerArithmeticOoperation
//
//  Created by 杨俊艺 on 2019/8/21.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

char *alloc(int n);
void afree(char *p);

int main(int argc, const char * argv[])
{
   
    
    
    
    
    
    
    
    return 0;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf; //下一个空闲位置

char *alloc(int n)//返回指向n个字符的指针
{
    if (allocbuf + ALLOCSIZE - allocp >= n)//如果有剩余空间则返回allocp当前值,即空闲块开始位置,然后加上n指向下一个空闲块
    {
        allocp += n;
        return allocp - n;
    }
    else//空间不够
        return 0;
}

void afree(char *p)//释放p指向的存储区
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)//如果p在allocbuf内则afree仅仅只是将allocp设置为p
    {
        allocp = p;
    }
}

//这两个函数是不完善的函数,因为对afree的调用次序必须与调用alloc的次序相反
//最容易实现的方法是让alloc函数对一个大字符数组allocbuf中的空间进行分配,该数组是这两个函数的私有数组
//由于这两个函数处理的对象是指针而不是数组下标,因此其他函数无需知道该数组的名字,使得可以在包含alloc和afree的源文件中将该数组声明为static类型对外部不可见
//实际实现时该数组甚至可以没有名字,通过调用malloc或向操作系统申请一个指向无名存储块的指针获得
