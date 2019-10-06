//
//  TokenBucket.c
//  TokenBucketLib
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "TokenBucket.h"

#define    min(a,b)    ((a) < (b) ? (a) : (b))

struct TokenBucket_st {
    int cps;
    int burst;
    int token;
    int pos;
};

static struct TokenBucket_st* job[TOKENBUCKETMAX];

static int GetFreePos(void)
{
    int i;
    for (i = 0; i < TOKENBUCKETMAX; i++) {
        if (job[i] == NULL) {
            return i;
        }
    }
    return -1;
}

static int inited = 0;

static sig_t alarm_handler_save;

static void alarm_handler(int s)
{
    int i;
    alarm(1);
    for (i = 0; i < TOKENBUCKETMAX; i++) {
        if (job[i] != NULL) {
            job[i]->token += job[i]->cps;
            if (job[i]->token > job[i]->burst) {
                job[i]->token = job[i]->burst;
            }
        }
    }
}

static void Module_UnLoad(void)
{
    int i;
    signal(SIGALRM, alarm_handler_save);//恢复
    alarm(0);
    for (i = 0; i < TOKENBUCKETMAX; i++) {
        free(job[i]);
    }
}

static void Module_Load(void)
{
    alarm_handler_save = signal(SIGALRM, alarm_handler);
    alarm(1);
    atexit(Module_UnLoad);
}

TokenBucket_t * TokenBucket_Init(int cps, int burst)
{
    struct TokenBucket_st *me = malloc(sizeof(*me));
    
    int pos = GetFreePos();
    if (pos < 0) {
        return NULL;
    }
    
    if (me == NULL) {
        return NULL;
    }
    
    if (!inited) {
        Module_Load();
        inited = 1;
    }
    
    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    me->pos = pos;
    
    job[pos] = me;
    
    return me;
}

int TokenBucket_FetchToken(TokenBucket_t *ptr, int size)
{
    struct TokenBucket_st *me = ptr;
    if (size <= 0) {
        return -1;
    }
    while (me->token <= 0) {
        pause();
    }
    int n = min(me->token, size);
    me->token -= n;//这里这句没打导致排错....
    return n;
}

int TokenBucket_ReturnToken(TokenBucket_t *ptr, int size)
{
    struct TokenBucket_st *me = ptr;
    if (size <= 0) {
        return -1;
    }
    me->token += size;
    if (me->token > me->burst) {
        me->token = me->burst;
    }
    return size;
}

int TokenBucket_Destory(TokenBucket_t *ptr)
{
    struct TokenBucket_st *me = ptr;
    job[me->pos] = NULL;
    free(ptr);
    return 0;
}
