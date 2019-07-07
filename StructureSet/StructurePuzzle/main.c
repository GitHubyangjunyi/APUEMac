//
//  main.c
//  StructurePuzzle
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    struct
    {
        int len;
        char *str;
    }*p;
    struct
    {
        int len;
        char *str;
    }st;
    p = &st;
    p->len = 100;
    p->str = "abcdefg";
    ++p->len;//增加len的值,隐含括号关系是++(p->len)
    printf("%d\n", p->len);
    printf("%s\n", p->str);
    
    //*p->str            读取指针str所指向的对象的值
    //*p->str++            读取指针str所指向的对象的值,str+1(与*str++相同)
    //(*p->str)++        将str指向的对象的值加1
    //*p++->str            读取指针str所指向的对象的值,p加1
    
    
    return 0;
}
