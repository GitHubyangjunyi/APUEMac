//
//  main.c
//  Mmapmini
//
//  Created by 杨俊艺 on 2019/6/15.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define NRECORDS (100)

typedef struct
{
    int integer;
    char string[24];
}RECORD;


int main(int argc, const char * argv[])
{
    //先定义一个RECORD数据结构然后创建出NRECORDS个记录
    //每个记录中保存着它们各自的编号,然后把这些记录都追加到文件records.dat里去
    RECORD record, *mapped;
    int i, f;
    FILE *fp;
    
    fp = fopen("records.dat", "w+");
    for (i = 0; i < NRECORDS; i++) {
        record.integer = i;
        sprintf(record.string, "RECORD-%d", i);
        fwrite(&record, sizeof(record), 1, fp);
    }
    fclose(fp);
    
    //接着把第43条记录中的整数值由43修改为143并把它写入第43条记录中的字符串
    fp = fopen("records.dat", "r+");
    fseek(fp, 43 * sizeof(record), SEEK_SET);
    fread(&record, sizeof(record), 1, fp);
    fclose(fp);
    
    //现在把这些记录映射到内存中然后访问第43条记录把它的整数值修改为243,同时更新该记录中的字符串,使用的还是内存映射的方法
    f = open("records.dat", O_RDWR);
    mapped = (RECORD *)mmap(0, NRECORDS * sizeof(record), PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
    mapped[43].integer = 243;
    sprintf(mapped[43].string, "RECORD-%d", mapped[43].integer);
    
    msync((void *)mapped, NRECORDS * sizeof(record), MS_ASYNC);
    close(f);
    
    
    
    
    
    
    
    
    return 0;
}
