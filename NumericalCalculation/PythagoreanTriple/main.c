//
//  main.c
//  PythagoreanTriple
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include<math.h>

int main(int argc, const char * argv[]) {
    
    
    int a, b, c, count = 0;
    printf("150以内的勾股数有：\n");
    printf("  a     b    c       a    b    c       a    b    c      a    b    c\n");
    for (a = 1; a <= 150; a++)
        for (b = a + 1; b <= 150; b++)
        {
            c = (int)sqrt(a * a + b * b);//求c值
            if (c * c == a * a + b * b && a + b > c && a + c > b && b + c > a && c <= 150)//判断c的平方是否等于a2+b2
            {
                printf("%4d %4d %4d    ", a, b, c);
                count++;
                if (count % 4 == 0)//每输出4组解就换行
                    printf("\n");
            }
        }
    printf("\n");
    
    
    return 0;
}

//勾股数
