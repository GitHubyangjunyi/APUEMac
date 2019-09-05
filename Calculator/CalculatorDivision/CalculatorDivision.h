//
//  CalculatorDivision.h
//  CalculatorDivision
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#ifndef CalculatorDivision_h
#define CalculatorDivision_h

#include <stdio.h>

#define NUMBER '0'    //表示找到一个数

void push(double);
double pop(void);

int getop(char[]);

int getch(void);
void ungetchs(int);

#endif /* CalculatorDivision_h */
