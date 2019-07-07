//
//  main.c
//  PascalTriangle
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int n = 50;
    int queue[42] = { 0,1,1,0 };
    int front = 1;//当前元素所在位置
    int rear = 4;//将要入队元素位置
    
    for (int i = 0; i < n; i++)
    {
        queue[rear] = queue[front - 1] + queue[front];//队尾插入两个元素和
        printf("%d ", queue[rear]);
        rear++;
        if (queue[front] == 0)//行分隔标记
        {
            queue[rear] = 0;//添加行分隔标记
            rear++;
            printf("\n");
        }
        front++;//队列头指针后移
    }
    
    return 0;
}

//杨辉三角形式如下:
//            1
//          1   1
//        1    2    1
//      1      3      3      1
//    1    4    6    4  1
//
//由二项式( a + b )的n次方展开后各项的系数排成的三角形,特点是左右两边都是1,从第二行起,中间的每个数都是上一行里相邻两个数之和
//在这个例子中,front指向的是即将要处理的数据,处理后的结果放入rear指向的序列尾部,作为新入队的数据,整个过程模型即是一个队列的形式
//
//在这个例子中,队列没有循环使用,若queue[]与循环次数设置不恰当,则数组queue有越界的危险
