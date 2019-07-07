//
//  main.c
//  SpecifiedInitialization
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

struct student
{
    char name[20];
    int age;
    int num;
};

int main(int argc, const char * argv[]) {
    
    int b[100] = { [10] = 1,[50 ... 60] = 2 };//使用范围匹配来指定初始化
    
    for (int i = 0; i < 100; i++)
    {
        printf("b[%d] = %d\t", i, b[i]);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    
    struct student stu = { "xxx",12 };//未初始化的成员为0
    printf("%s %d %d\n", stu.name, stu.age, stu.num);
    
    struct student stus =
    {
        .age = 16,
        .name = "yyy",
        .num = 111,
    };
    printf("%s %d %d\n", stus.name, stus.age, stus.num);
    
    
    return 0;
}

//指定初始化
//此项目需在Linux环境下编译运行
