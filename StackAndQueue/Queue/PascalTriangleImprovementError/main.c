//
//  main.c
//  PascalTriangleImprovementError
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define M 8    //循环队列长度8

int main(int argc, const char * argv[]) {
   
    int n = 63;//二项式方次63
    int queue[M] = { 0,1,1,0 };
    int front = 1;//当前元素所在位置
    int rear = 4;//将要入队元素位置
    
    for (int i = 0; i < n; i++)
    {
        //不添加队满条件判断,出错
        /*if ((rear + 1) % M == front)
         {
         break;
         }*/
        queue[rear] = queue[(front - 1 + M) % M] + queue[front];//队尾插入两个元素和
        printf("%d ", queue[rear]);
        //rear++;
        rear = (rear + 1) % M;
        if (queue[front] == 0)//行分隔标记
        {
            queue[rear] = 0;//添加行分隔标记
            //rear++;
            rear = (rear + 1) % M;
            printf("\n");
        }
        //front++;//队列头指针后移
        front = (front + 1) % M;
    }
    
    printf("\n添加队满条件判断\n");
    n = 63;//二项式方次63
    int queues[M] = { 0,1,1,0 };
    front = 1;//当前元素所在位置
    rear = 4;//将要入队元素位置
    
    
    for (int i = 0; i < n; i++)
    {
        //添加队满条件判断
        if ((rear + 1) % M == front)
        {
            break;
        }
        queues[rear] = queues[(front - 1 + M) % M] + queues[front];//队尾插入两个元素和
        printf("%d ", queues[rear]);
        //rear++;
        rear = (rear + 1) % M;
        if (queues[front] == 0)//行分隔标记
        {
            queues[rear] = 0;//添加行分隔标记
            //rear++;
            rear = (rear + 1) % M;
            printf("\n");
        }
        //front++;//队列头指针后移
        front = (front + 1) % M;
    }
    
    char GETCHAR = getchar();
    return 0;
}

//这个求解过程出错,原因在于front = rear时,队列状态满,再入队会产生队尾元素覆盖队头元素的现象
//改进的办法是在for循环的第一条加上队满判断,跳出循环
//循环队列在使用过程中,因为队长有限,当入队的速度大于出队速度时,会产生队尾元素覆盖队头元素的现象,即队列"溢出"
