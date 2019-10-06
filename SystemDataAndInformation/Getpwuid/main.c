//
//  main.c
//  Getpwuid
//
//  Created by 杨俊艺 on 2019/9/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {
    
    struct passwd *pwds;
    
    if (argc < 2) {
        fprintf(stderr, "Usage...\n");
        exit(0);
    }
    
    pwds = getpwuid(atoi(argv[1]));
    
    puts(pwds->pw_name);
    
    
    
    //下面是关于校验用户名和密码的程序
    //编译时链接-lcrypt
    //使用管理员权限运行./xxx 用户名
    //详情查看B站视频嵌入式开发-APUE 李慧芹 3-2-7
//    char *input_pass;
//    struct spwd *shadowline;
//    char *crypted_pass;
//
//    if (argc < 2) {
//        fprintf(stderr, "Usage...\n");
//        exit(0);
//    }
//
//    input_pass = getpass("PassWord:");
//
//    shdowline = getspnam(argv[1]);
//
//    crypted_pass = crypt(input_pass, shadowline->sp_pwdp);
//
//    if (strcmp(shadowline->sppwdp, crypted_pass) == 0) {
//        puts("OK!")
//    }
//    else{
//        puts("Failed!");
//    }
//
    
    return 0;
}
