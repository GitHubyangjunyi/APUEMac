//
//  main.c
//  Getopt
//
//  Created by 杨俊艺 on 2019/6/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    int opt;
    //getopt函数将传递给程序的main函数的argc和argv作为参数的同时接受一个选项指定符字符串optstring告诉getopt哪些选项可用以及它们是否有关联值
    //optstring只是一个字符列表每个字符代表一个单字符选项
    //如果一个字符后面紧跟一个冒号:则表明该选项有一个关联值作为下一个参数
    //./Getopt -i -lr 'hi there' -f fred.c
    while ((opt = getopt(argc, argv, ":if:lr:")) != -1) {
        switch (opt) {
            case 'i':
            case 'l':
            case 'r':
                printf("option: %c\n", opt);//opt是argv数组中的下一个选项字符如果有的话
                break;
            case 'f':
                printf("filename: %s\n", optarg);//optarg保存关联值
                break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);//optopt保存无法识别的选项
            default:
                break;
        }
    }
    
    for (; optind < argc; optind++)
        printf("argument: %s\n", argv[optind]);
    

    
    
    
    
    return 0;
}

//getopt的返回值是argv数组中的下一个选项字符如果有的话,循环调用getopt就可以依次得到每个选项
//getopt有如下行为
//如果选项有一个关联值则外部变量optarg指向这个值
//如果选项处理完毕getopt返回-1,特殊参数将使getopt停止扫描选项
//如果遇到一个无法识别的选项getopt返回一个问号?并把它保存到外部变量optopt中
//如果一个选项要求有一个关联值(例如例子中的f)但用户并未提供这个值则getopt通常将返回一个问号
//如果我们将选项字符串的第一个字符设置为冒号,那么getopt将在用户未提供值的情况下返回冒号而不是问号
//外部变量optind被设置为下一个待处理参数的索引.getopt利用它来记录自己的进度,程序很少需要对这个变量进行设置
//当所有选项参数都处理完毕后optind将指向argv数组尾部可以找到其余参数的位置
//每个选项（包括未知选项和缺少关联值的选项）都有相应的处理动作
//当所有选项都处理完毕后程序像以前一样把其余参数都打印出来,但这次是从optind位置开始
//./Getopt -i -lr 'hi there' -f fred.c -q
//option: i
//option: l
//option: r
//filename: fred.c
//unknown option: q
