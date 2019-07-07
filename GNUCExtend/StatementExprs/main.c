//
//  main.c
//  StatementExprs
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int sum = 0;
    sum=
    ({
        int s = 0;
        for (int i = 0; i < 10; i++)
            s = s + i;
        s;
    });
    printf("sum = %d\n", sum);//45
    
    sum =
    ({
        int s = 0;
        for (int i = 0; i < 10; i++)
            s = s + i;
        s = 100;
    });
    printf("sum = %d\n", sum);//100
    
    sum = 0;
    sum =
    ({
        int s = 0;
        for (int i = 0; i < 10; i++)
            s = s + i;
        goto here;
        s;
    });
    printf("sum = %d\n", sum);
    
here:
    printf("here:\n");
    printf("sum = %d\n", sum);//0
    

    return 0;
}

//表达式的后面加一个;就构成了一条基本的语句
//编译器在编译解析程序时不是根据物理行而是根据分号;来判断一条语句的结束标记的
//GNU C对C标准作了扩展允许在一个表达式里内嵌语句
//允许在表达式内部使用局部变量/for循环和goto语句
//这样的表达式我们称之为语句表达式
//语句表达式的格式如
//({ 表达式1; 表达式2; 表达式3; })
//语句表达式跟一般表达式一样也有自己的值,语句表达式的值为内嵌语句中后一个表达式的值
