//
//  AlarmMulti.h
//  AlarmMulti
//
//  Created by 杨俊艺 on 2019/9/20.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#ifndef AlarmMulti_h
#define AlarmMulti_h

#include <stdio.h>
#include <errno.h>

#define JOB_MAX 024

typedef void at_jobfunc_t(void *);

int at_addjob(int sec, at_jobfunc_t *jobp, void *arg)
{
    //返回值大于等于0  成功,返回任务ID
    //== -EINVAL    失败,参数非法
    //== -ENOSPC    失败,数组空间已满
    
    
    
    
    
    
    
    
    
    return 0;
}

int at_canceljob(int id)
{
    //返回值等于0    成功,指定任务成功取消
    //== -EINVAL    失败,参数非法
    //== -ENOSPC    失败,任务数组空间已满
    //== -EBUSY     失败,指定任务已经完成
    //== -ECANCELED 失败,指定任务重复取消
    
    
    
    
    
    
    
    
    return 0;
    
}

int at_waitjob(int id)
{
    //返回值等于0    成功释放指定任务
    //== -EINVAL    失败,参数非法
    //==
    
    
    
    
    
    
    
    
    return 0;
}



#endif /* AlarmMulti_h */
