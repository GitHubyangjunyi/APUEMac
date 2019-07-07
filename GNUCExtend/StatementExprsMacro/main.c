//
//  main.c
//  StatementExprsMacro
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

#define MAX(x,y) x > y ? x : y
#define MAX_TWO(x,y) (x) > (y) ? (x) : (y)
#define MAX_THREE(x,y) ((x) > (y) ? (x) : (y))
#define MAX_FOUR(x,y)({\
        int _x = x;\
        int _y = y;\
        _x > _y ? _x : _y;\
})

#define MAX_FIVE(type,x,y)({\
        type _x = x;\
        type _y = y;\
        _x > _y ? _x : _y;\
})

#define MAX_SIX(x,y)({\
        typeof(x) _x = x;\
        typeof(y) _y = y;\
        (void) (&_x == &_y);\
        _x > _y ? _x : _y;\
})
//(void) (&_x == &_y);
//用来检测宏的两个参数x和y的数据类型是否相同
//对于不同类型的指针比较编译器会给一个警告提示两种数据类型不同
//语句&_x == &_y用来判断两个变量_x和_y的地址是否相等,即比较两个指针是否相等
//&_x == &_y分别表示两个不同变量的地址怎么可能相等呢!既然大家都知道内存中两个不同的变量地址肯定不相等
//那为什么还要在此多此一举呢?妙就妙在当两个变量类型不相同时,对应的地址即指针类型也不相同
//比如一个int型变量和一个char变量,对应的指针类型分别为char *和int *,而两个指针比较必须是同种类型的指针否则编译器会有警告信息
//二是当两个值比较的结果没有用到,有些编译器可能会给出一个warning
//加个(void)后就可以消除这个警告

#define SWAP(a,b)\
do\
{\
typeof(a) _temp = (a); \
(a) = (b); \
(b) = _temp;\
} while (0);


int main(int argc, const char * argv[]) {
    
    printf("MAX=%d\n", MAX(1, 2));
    printf("MAX=%d\n", MAX(2, 1));
    printf("MAX=%d\n", MAX(2, 2));
    printf("MAX=%d\n", MAX(1 != 1, 1 != 2));//期望得到1但是得到的是0
    
    printf("MAX=%d\n", 1 != 1 > 1 != 2 ? 1 != 1 : 1 != 2);//比较运算符>的优先级为6大于!=的优先级7,运算顺序都是从左到右
    
    printf("MAX=%d\n", 1 != 0 != 2 ? 1 != 1 : 1 != 2);//运算顺序都是从左到右
    
    ////MAX_TWO////
    printf("MAX_TWO=%d\n", 3 + MAX_TWO(1, 2));//预期5实际结果1
    //                 3 + (1) > (2) ? (1) : (2)
    //运算符+的优先级大于比较运算符>
    
    ////MAX_THREE////
    int i = 2;
    int j = 6;
    printf("MAX_THREE=%d\n", MAX_THREE(i++, j++));//预期6实际结果7,因为变量i和j在宏展开后做了两次自增运算,导致打印出i的值为7
    
    
    ////MAX_FOUR////
    i = 2, j = 6;
    printf("MAX_FOUR=%d\n", MAX_FOUR(i++, j++));//6
    
    ////MAX_FIVE////
    printf("MAX_FIVE=%f\n", MAX_FIVE(float, 3.14, 3.15));//3.15
    
    ////MAX_SIX////
    printf("MAX_SIX=%f\n", MAX_SIX(33, 3.15));
    
    ////SWAP////
    int a = 1;
    int b = 2;
    printf("a = %d\n", a);//1
    printf("b = %d\n", b);//2
    
    SWAP(a, b);
    printf("a = %d\n", a);//2
    printf("b = %d\n", b);//1
    

    return 0;
}
