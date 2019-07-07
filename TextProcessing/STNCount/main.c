//
//  main.c
//  STNCount
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int c;
    int nb;
    int nt;
    int nl;
    
    nb = nt = nl = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            ++nb;
        if (c == '\t')
            ++nt;
        if (c == '\n')
            ++nl;
    }
    printf("Space %d\nTab %d\nEnter %d\n", nb, nt, nl);
    
    
    return 0;
}
