//
//  main.c
//  PascalTriangleImprovement
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define M 32    //循环队列长度32

int main(int argc, const char * argv[]) {
    
    int n = 63;//二项式方次63
    int queue[M] = { 0,1,1,0 };
    int front = 1;//当前元素所在位置
    int rear = 4;//将要入队元素位置
    
    for (int i = 0; i < n; i++)
    {
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
    
    
    return 0;
}
