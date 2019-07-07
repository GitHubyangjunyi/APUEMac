//
//  main.c
//  PIApproach
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
   
    
    float x = 4;
    int i = 1, m = 1;
    while (1)//循环次数无法事先确定,使用条件判断来结束循环
    {
        x = x + (float)(-1)*m * 4 / (2 * i + 1);
        i++;
        m = m * (-1);
        printf("i=%d,x=%f\n", i, x);
        if (x>=3.14-0.00001&&x<=3.14+0.000001)//用来控制精确度,实数不能直接比相等
        {
            break;
        }
    }
    
    return 0;
}

//可以见CPlusPlus解决方案下的ProgressionApproximation 级数逼近
//以及Java项目下的蒙特卡洛求PI
//PI=4-4/3+4/5-4/7+4/9-4/11+...
//除第一项外的通项公式(-1)*m * 4 / (2 * i + 1)
//
//                算法顶部伪代码描述
//    赋初值: 累加和x = 4  m = 1 项数i = 1
//    根据通用公式,x做循环累加
//    输出值以及项数
//    直到x = 3.14时中断循环
//
//                算法细化描述
//    累加和x = 4; m = 1; i = 1
//    do
//        x = x + (float)(-1)*m * 4 / (2 * i + 1);
//        i++;
//        m = m * (-1);
//        输出值以及项数
//    until x = 3.14时中断
