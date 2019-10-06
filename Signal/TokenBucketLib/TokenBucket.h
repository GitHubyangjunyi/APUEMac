//
//  TokenBucket.h
//  TokenBucketLib
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#ifndef TokenBucket_h
#define TokenBucket_h

#define TOKENBUCKETMAX 1024

typedef void TokenBucket_t;

TokenBucket_t * TokenBucket_Init(int cps, int burst);

int TokenBucket_FetchToken(TokenBucket_t *, int);

int TokenBucket_ReturnToken(TokenBucket_t *, int);

int TokenBucket_Destory(TokenBucket_t *);

#endif /* TokenBucket_h */
