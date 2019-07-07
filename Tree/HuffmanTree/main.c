//
//  main.c
//  HuffmanTree
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#define N 26        //页结点数也作为哈夫曼编码位数
#define M 2*N-1        //数的结点总数
#define MAXSIZE  128//要译码的字符串或哈夫曼编码串长度

typedef int datatype;

typedef struct  //结点结构体
{
    char data;    //结点值
    int weight;    //权值
    int parent;    //双亲结点
    int lchild;    //左孩子结点
    int rchild;    //右孩子结点
}HuffmanTreeNode;

typedef struct //编码结构体
{
    char bit[N];//存放哈夫曼编码
    int start;    //从start开始读bit中的哈夫曼码
}HuffmanCodeNode;

int main(int argc, const char * argv[]) {
    
    
    
    
    
    return 0;
}
