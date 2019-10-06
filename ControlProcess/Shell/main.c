//
//  main.c
//  Shell
//
//  Created by 杨俊艺 on 2019/9/16.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>

#define DELIMS " \t\n"

struct cmd_str//定义成结构体方便以后扩展
{
    glob_t globres;
};

static void parse(char *bufline, struct cmd_str *res);

int main(int argc, const char * argv[])
{
    pid_t pid;
    char *linebuf = NULL;
    size_t linebufsize = 0;
    struct cmd_str cmd;
    
    while (1) {
        
        printf("Shell#");
        
        if ((getline(&linebuf, &linebufsize, stdin)) < 0) {
            break;
        }
        
        parse(linebuf, &cmd);
        
        if (0)
        {
            //如果是内部命令不进行处理
            continue;
        }
        else//如果是外部命令
        {
            if ((pid = fork()) < 0) {
                perror("fork:");
                exit(1);
            }
            if (pid ==0) {
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp:");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }

    }
    
    exit(0);
}

void parse(char *bufline, struct cmd_str *res)
{
    //strtok
    //strsep
    
    char *tok;
    int i = 0;
    
    while (1) {
        tok = strsep(&bufline, DELIMS);
        if (tok == NULL) {
            break;
        }
        if (tok[0] == '\0') {
            continue;
        }
        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres);
        i = 1;
    }
}
