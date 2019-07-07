//
//  main.c
//  Typedef
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    typedef char *ptr_to_char;//一般使用这个,在其他格式上悬停鼠标即可看到通常使用这一格式
    //自由格式,都可以
    //typedef char * ptr_to_char;
    //typedef char* ptr_to_char;
    //typedef char*ptr_to_char;
    ptr_to_char a;
    a = "ptr_to_char";
    printf("%s\n", a);
    
    
    typedef struct player
    {
        int num;
        int age;
    }Player_st,*player_ptr;
    /*
     typedef struct player
     {
     int num;
     int age;
     }*
     *///的别名是player_ptr
    
    struct player playerone;
    playerone.num = 10;
    playerone.age = 20;
    
    Player_st playertwo;
    playertwo.num = 11;
    playertwo.age = 22;
    
    
    player_ptr ptrtype = malloc(sizeof(Player_st));//must mallco
    //ptrtype.age = 111;//error
    ptrtype->age = 111;
    ptrtype->num = 222;

    
    return 0;
}

//Typedef 定义数据类型新名字
//C语言提供了Typedef的功能用来建立新的数据类型名
//typedef int Length;
//将Length定义为与int具有同等意义的名字,类型Length可以用来类型声明,类型转换等,和类型int完全相同
//类似地:
//typedef char *String
//将String定义为与char*或字符指针同义
