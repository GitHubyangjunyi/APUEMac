//
//  main.c
//  AAAAReadMe
//
//  Created by 杨俊艺 on 2019/6/12.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {
    
    //测试指定前驱的scanf
    //int num;
    //scanf("hello %d", &num);
    //printf("%d", num);
    
    //测试范围匹配
//    char c;
//    int n;
//    float f;
//    char s[256];
//    scanf("hx, %c, %d, %g, %[^\n]", &c, &n, &f, s);
//    printf("%c\n", c);
//    printf("%d\n", n);
//    printf("%f\n", f);
//    printf("%s\n", s);
//    scanf("%s", s);
//    printf("%s\n", s);
    
    
    
    
    int *a = malloc(sizeof(int));
    *a = 100;
    
    int *b = malloc(sizeof(int));
    *b = 2;
    
    free(a);
    
    int *c = malloc(sizeof(int));
    *c = 30;
    
    
    printf("%d, %d, %d\n", *a, *b, *c);
    
    
    
    
    
    
    
    
    
    
    return 0;
}

//新建Xcode项目，然后使用target管理不同的小项目，每个target将运行不同的main函数

/*
 //参考书目:
//The C Programming Language Brian W.Kernighan/Dennis M.Ritchie 著
//数据结构与算法分析新视角 周幸妮/任智源/马彦卓/樊凯 著
//C Primer Plus Stephen Prata 著
//C和指针 Kenneth A.Reek 著
//C陷阱与缺陷 Andrew Koenig 著
//C程序设计新思维 Ben Klemens 著(讲解了使用CLang在Visual Studio调试C)
//标准C语言指南 李忠 著
//深入理解程序设计使用Linux汇编语言 Jonathan Bartlett 著(附录中带有简单GUI/汇编语言中的常用C语句/GDB快速参考)
//操作系统真相还原 郑钢 著(关于内联汇编)
//跟我一起写Makefile 陈皓 著
//C现代编程:集成开发环境/设计模式/极限编程/测试驱动开发/重构/持续集成(关于C如何实现面向对象)
//图灵社区 码农周刊第26期 经典C++
//嵌入式C语言自我修养 王利涛 著 知乎专栏 (主要是讲解GNU C语言语法扩展)
//Linux环境编程:从应用到内核
//Linux程序设计
*/

/*
//K&R C一般称为传统C,ANSI C是美国国家标准协会在K&R C的基础上,统一各大编译器厂商而产生的标准,一般叫做C89或C90
//C语言关键字和保留字符(C90表示从C90标准开始加入)
//
//    auto            extern          short          while
//    break           float           signed(C90)    _Alignas(C11)
//    case            for             sizeof         _Alignof(C11)
//    char            goto            static         _Atomic(C11)
//    const(C90)      if              struct         _Bool(C99)布尔型
//    continue        inline(C99)内联  switch         _Complex(C99)复数
//    default         int             typedef        _Generic(C11)泛型编程
//    do              long            union          _Imaginary(C99)虚数
//    double          register        unsigned      _Noreturn(C11)声明函数无返回值
//    else     restrict(C99)指针修饰符  void          _Static_assert(C11)
//    enum(C90)       return         volatile(C90)  _Thread_local(C11)
//
//void *数据类型是ANSI C加入的
//C99新增特性:
//    long long和long double以及float_Complex
//    变长数组,数组的长度可以由变量来指定
//        int b;
//        int a[b];
//    允许结构体特定成员赋值
//    指针修饰符restrict
//restrict是c99标准引入的,它只可以用于限定和约束指针并表明指针是访问一个数据对象的唯一且初始的方式
//即它告诉编译器,所有修改该指针所指向内存中内容的操作都必须通过该指针来修改,而不能通过其它途径(其它变量或指针)来修改
//这样做的好处是,能帮助编译器进行更好的优化代码,生成更有效率的汇编代码,如 int *restrict ptr,ptr指向的内存单元只能被ptr访问到
//任何同样指向这个内存单元的其他指针都是未定义的,就是无效指针
 */

/*
//运算符优先级
//
//            运算符        名称或含义        使用形式            结合方向    说明
//1级别                                                       从左到右
//            []            数组下标        数组名[常量表达式]
//            ()            圆括号         (表达式)/函数名(形参表)
//            .             成员选择(对象)   对象.成员名
//            ->            成员选择(指针)   对象指针->成员名
//2级别                                                       从右到左    单目运算符
//            -             负号运算符       -表达式
//            ~             按位取反运算符    ~表达式
//            ++            自增运算符      ++变量名/变量名++
//            --            自减运算符      --变量名/变量名--
//            *             取值运算符       *指针变量
//            &             取地址运算符     &变量名
//            !             逻辑非运算符     !表达式
//            (类型)         强制类型转换   (数据类型)表达式
//            sizeof        长度运算符      sizeof(表达式)
//3级别                                                       从左到右    双目运算符
//            /             除              表达式/表达式
//            *             乘              表达式*表达式
//            %             取模(余数)      整型表达式%整型表达式
//4级别                                                       从左到右    双目运算符
//            +             加              表达式+表达式
//            -             减              表达式-表达式
//5级别                                                       从左到右    双目运算符
//            <<            左移            变量<<表达式
//            >>            右移            变量>>表达式
//6级别                                                       从左到右    双目运算符
//            >             大于            变量>表达式
//            >=            大于等于         变量>=表达式
//            <             小于            变量<表达式
//            <=            小于等于         变量<=表达式
//7级别                                                       从左到右    双目运算符
//            ==            等于            表达式==表达式
//            !=            不等于          表达式!=表达式
//8级别                                                       从左到右    双目运算符
//            &             按位与           表达式&表达式
//9级别                                                       从左到右    双目运算符
//            ^             按位异或         表达式^表达式
//10级别                                                      从左到右    双目运算符
//            |             按位或           表达式|表达式
//11级别                                                      从左到右    双目运算符
//            &&            逻辑与           表达式&&表达式
//12级别                                                      从左到右    双目运算符
//            ||            逻辑或           表达式||表达式
//13级别                                                      从右到左    三目运算符
//            ?:            条件运算符     表达式1?表达式2:表达式3
//14级别                                                      从右到左
//            =             赋值运算符        变量=表达式
//            /=            除后赋值         变量/=表达式
//            *=            乘后赋值         变量*=表达式
//            %=            取模后赋值        变量%=表达式
//            +=            加后赋值         变量+=表达式
//            -=            减后赋值         变量-=表达式
//            <<=           左移后赋值        变量<<=表达式
//            >>=           右移后赋值        变量>>=表达式
//            &=            按位与后赋值      变量&=表达式
//            ^=            按位异或后赋值    变量^=表达式
//            |=            按位或后赋值      变量|=表达式
//15级别                                                     从左到右
//            ,             逗号运算符        表达式,表达式,...
*/

//项目索引
//AAAAReadMe
//Algorithm         算法
    //Backtracking          回溯法
    //BranchAndBound        分支限界法
    //DivideAndConquer      分治法
    //DynamicProgramming    动态规划法
        //1//FibonacciDynamicProgramming 斐波那契数列高效率动态规划版
    //ExhaustionReadMe      穷举法
    //Greedy                贪心法
    //Iterative             迭代法
    //Recurrence            递推法
    //Recursion             递归法
        //5//ArrayReverseRecursion  数组倒置递归(未完成)
        //0//ArraySumRecursion      数组求和,线性递归
        //6//FibonacciRecursion     斐波那契数列低效率递归版
        //3//ItoaRecursion          通过递归调用将整数转换成字符串
        //1//Printd                 打印十进制数
        //4//ReverseRecursion       递归版本的reverse函数,将字符串s倒置(相关TextProcessing/Reverse reverse函数,将字符串s倒置)
//ArrayPointer      数组指针操作
//BitsProcessing    位处理
    //假定最右边的一位是第0位,getbits(x,4,3)返回第4,3,2位,方向是从左到右,从左到右,从左到右
    //5//BitCount           统计x中值为1的二进制位数 练习2-9
    //1//Getbits            返回x中从第p位开始的n位
    //3//Invert             返回对x执行下列操作后的结果值:将x中从第p位开始的n个位求反,x的其余各位保持不变 练习2-7
    //4//Rightrot           返回将x循环右移n位后得到的值 练习2-8
    //2//Setbits            返回对X执行下列操作后的结果值:将x中从第p位开始的n个位设置为y中最右边n位的值,x的其余各位保持不变 练习2-6
//BlockStructure    作用域规则
//BlockStructureFix 作用域规则static
//BlockStructurePro 作用域规则之程序员的自我修养
//Calculator        计算器
    //2//CalculatorDivision 拆分版本
    //1//CalculatorOne      初始版本
//ConditionalCompilation    条件编译
//ConstRestrict     const限定
//EOFS              EOF测试
//FileAPI           系统调用文件API
    //3//Close
    //4//Copy
    //5//CopySlow
    //8//Iotcl
    //7//Open               创建文件并测试文件的属性
    //2//Read               测试文件所具有的属性
    //6//Stat
    //1//Write
//FileAPIStd        标准I/O库文件API
    //2//CopyStd
    //3//ErgodicDir         递归遍历文件夹
    //4//ErgodicDirImpru    递归遍历文件夹改进版本,可以通过命令行参数指定文件夹
    //1//Fopen
    //5//Mnapmini           内存映射函数文件共享
//FirstDemo         C和指针第一章的Demo
//FormatControl     格式控制
//FunctionPointer   函数指针
//GNUCExtend        GNUC扩展
    //11//Atttribute            特殊属性
    //17//AtttributeAlias       函数别名
    //13//AtttributeAligned     增大地址对齐
    //18//AtttributeAlwaysInline内联展开
    //15//AtttributeFormat      变参函数的参数格式检查
    //14//AtttributePacked      减少地址对齐
    //12//AtttributeSection     编译段指定
    //16//AtttributeWeak        强符号转换为弱符号
    //19//Builtin               内建函数
    //21//BuiltinConstantp      内建函数编译优化
    //22//BuiltinExpect         内建函数分支预测优化
    //20//BuiltinFrameAddress   函数栈帧地址
    //23//BuiltinLikelyUnLikely 内建函数分支预测优化
    //7//ContainerOfMacro       内核第一宏使用示例
    //6//ContainerOfMacroPre    内核第一宏解析
    //0//CurrentFunctionName    获得当前函数名
    //10//FlexibleArray         柔性数组成员
    //9//FlexibleArrayApply     柔性数组在USB驱动中的应用
    //8//FlexibleArrayPre       柔性数组成员
    //28//GNUCExtendAmbiguity   可变参数宏歧义规避
    //26//GNUCMacroExtend       可变参数宏的另一种写法
    //27//GNUCMacroExtendApply  可变参数宏在内核中的应用
    //25//GNUCMacroExtendFix    可变参数宏修正
    //24//GNUCMacroExtendPre    可变参数宏简介
    //29//LockMacro             实现锁机制的宏
    //1//RangeMatch             范围匹配
    //2//SpecifiedInitialization指定初始化
    //3//StatementExprs         语句表达式(宏构造利器)
    //4//StatementExprsMacro    语句表达式宏
    //5//Typeof                 获得类型
//HighToLow         大小端问题
//InlineAssembleSet 内嵌汇编
    //InlineAssembleEight       内存约束损坏通知二&独占
    //InlineAssembleEleven      机器模式hbwk
    //InlineAssembleFive        名称占位符
    //InlineAssembleFour        序号占位符之字长限定(机器模式相关)
    //InlineAssembleNine        立即数约束iFIJNOX以及通用约束0到9
    //InlineAssembleOne         基本内联汇编寄存器约束
    //InlineAssembleSeven       立即数约束损坏通知一m
    //InlineAssembleSix         操作数类型修饰符=+&
    //InlineAssembleTen         机器模式hbwk
    //InlineAssembleThree       内存约束mo
    //InlineAssembleTwo         寄存器约束abcdDSqrgAftu
//LinkedList        链表
    //3//CircleLinkedList       循环链表
    //4//DoubleWayLinkedList    双向链表(一个结点结构既有前驱地址又有后继地址)
    //6//LinkedListPolynomial   单链表一元多项式计算(两个数据域的单链表,来自书本的部分函数还不是很完善,特殊情况无法最优化处理)
    //7//MINEOSListTest         一个64位操作系统的设计与实现中lib.h里的list数据结构测试
    //5//PrintSingleLinkedList  逆序输出单链表结点值测试用例
    //1//SequentialList         顺序表(将线性表的元素依次存放在一个连续的存储空间中)
    //2//SingleLinkedList       单链表(每个结点只有一个链域的链表)
//MacroSet          宏定义相关
    ////MacroDefinition         宏定义及宏定义的副作用
    ////Macrosubstitution       宏替换
    ////Va_list                 可变长参数
    ////Va_listCPlusPlus        可变长参数C++版
//MemoryManagement  内存管理(主要收集了来自图灵社区 码农周刊第26期 经典C++ 中的关于内存管理的内容)
    //5//Alloca                 变长数组VLA
    //3//Calloc                 分配时清空内存的内存分配函数
    //7//DanglingPointer        迷途指针(悬空指针)
    //9//DanglingPointerThree   迷途指针(悬空指针)使用块语句产生的迷途指针,顺便提了下垃圾回收
    //8//DanglingPointerTwo     迷途指针(悬空指针)更难察觉的迷途指针:一个以上的指针引用同一块内存区域而其中一个指针被释放
    //6//Free                   重复释放/迷途指针(悬空指针)
    //2//Malloc                 堆管理器
    //10//MallocTest            返回局部量的地址的函数测试用例
    //11//MallocTestTwo         返回局部量的地址的函数测试用例
    //1//MemoryLeak             内存泄漏的各种姿势,过度分配,内存丢失跟踪,完全丢失地址,丢失起始地址,隐式泄漏
    //0//NULLPointer            空指针的逻辑取反操作(来自知乎)
    //4//Realloc                内存块重新分配
//Memset            内存块操作函数memset
//NumericalCalculation  数值计算
    ////Factorial               阶乘n!
    ////Fibonacci               斐波那契数列
    ////PIApproach              PI逼近以及实数不能直接比相等
    ////Polynomial              多项式计算(空间复杂度)
    ////Power                   计算整数base的n次幂
    ////PythagoreanTriple       勾股数
//OOPAbstract           面向对象方法
//PerformanceTesting    性能测试
//POSIXThread           POSIXT线程
    //2//DeadLock               死锁
    //1//MultiThreadCounter     多线程计数器冲突
    ////
//Search                搜索
    //1//Binsearch              折半查找(数组v必须以升序排列) 练习3-1
//Sort                  排序算法
    //QuickSort                 快速排序(C.A.R.Hoare于1962年) P74
    //ShellSort                 Shell排序(D.L.Shell于1959年) P51
//StackAndQueue         运算受限的线性表----栈和队列
    //队列
        //5//LinkedQueue        链队列
        //1//PascalTriangle     杨辉三角的队列解法
        //2//PascalTriangleImprovement      杨辉三角的队列解法改进版(循环队列)
        //3//PascalTriangleImprovementError 杨辉三角的队列解法改进版(循环队列)故意出错版,循环队列溢出
        //6//PascalTriangleLinkedQueue      杨辉三角的链队列解法
        //7//RadixSort          基数排序(桶排序)
        //4//SequentialQueue    顺序队列(按循环队列规则操作)
    //栈
        //2//LinkStack          链栈
        //1//SequentialStack    顺序栈
        //3//StackConversion    数制转换
        //4//StackRecursion     栈实现递归
    //环形队列相关算法是固定缓冲区读写的常用模式
//StructureSet  结构
    //5//BitField               位域
    //1//StructPointers         指向结构的指针以及运算符->
    //2//StructPointersLite     指向结构的指针以及运算符->简化版(来自C和指针 Kenneth A.Reek 著)
    //3//StructPointersMajor    指向结构的指针以及运算符->专业版(来自知乎->与.运算符的区别,然而我把知乎的专业内容搬运到StructPointersLite那边了)
    //4//StructurePuzzle        *和->结合
//SystemEnvironment 系统环境信息的获取
    //APUEMac                   如何写好一个main函数的参数验证//未修正
    //1//ArgCheck               参数验证
    //2//Getopt                 参数获取函数//有偏差
    //
//TextProcessing    文本处理
    //标准库提供的输入/输出模型:
    //无论文本从何处输入,输出到何处,其输入/输出都是按照字符流的方式处理,文本流是多行字符构成的字符序列,而每行字符则由0个或多个字符组成,行末是一个换行符
    //getchar()函数从文本流中读入下一个输入字符,并将其作为结果值返回
    //putchar(c)将把整型变量c的内容以字符的形式打印出来

    //换行符并不是输入结束,而是将键盘上敲下的字符送入输入缓冲区供函数使用
    //Ctrl+Z表示一个字符,其ASCII码为26
    //只有当Ctrl+Z单独位于一行的行首时才表示输入的终止EOF,即无论何时都推荐先回车,再Ctrl+Z,再回车结束输入
    //当Ctrl+Z位于行中和行末时输入都不会结束,而是结束当前行的输入
    //且第一个Ctrl+Z作为ASCII码为26字符并入前面输入,并且在第一个Ctrl+Z后输入的字符和回车将不存入当前行,但输入回车有换行效果
    //Linux下用Ctrl+D

    //37//Atof                      将数字串s转换成相应的双精度浮点数,包括简单计算器程序 练习4-2
    //25//Atoi                      将数字串S转换成相应的整型数
    //10//CharClassifiedStatistics  字符分类统计:统计各个数字,空白符及其他字符出现的次数
    //30//CharClassifiedStatisticsSwitch  字符分类统计:统计各个数字,空白符及其他字符出现的次数(Switch版) P48
    //2//CharCount                  字符统计
    //23//DeleteNote                功能是删除注释 练习1-23
    //20//Detab                     将输入中的制表符替换成适当数目的空格,使空格充满到下一个制表符终止的地方 练习1-20(扩展练习5-11和5-12)
    //21//Entab                     将空格串替换为最少数量的制表符和空格,但要保持单词之间的间隔不变 练习1-21(扩展练习5-11和5-12)
    //31//Escape                    escape(s,t)将字符串t复制到字符串s中,并在复制过程中将换行符,制表符等不可见字符分别转换成\t\n等相应的可见的转义字符序列,再写一个相反功能的函数 练习3-2
    //6//EscapeCharacterRestore     转义字符还原 练习1-10
    //32//Expand                    expand(s1,s2)将字符串s1中类似a-z一类的速记符号在字符串s2中扩展为完全等价的完整列表abc...xyz,该函数可以处理大小写,并且可以处理a-b-c,a-z0-9与-a-z等类似的情况,作为前导和尾随的-字符原样输出 练习3-3
    //22//FoldLine                  将较长的输入行折成短一些的两行或多行,折行的位置在输入行的第n列之前的最后一个非空格字符之后 练习1-22
    //18//FormatTailBlanks          删除每个输入行末尾的空格及制表符,并删除完全是空格的行 练习1-18
    //11//FrequencyHistogram        频度直方图:打印输入中各个字符出现频度的直方图 练习1-14
    //12//Histogram                 单词长度直方图(水平):打印输入中单词长度的直方图 练习1-13
    //13//HistogramVersionTwo       单词长度直方图(垂直):打印输入中单词长度的直方图 练习1-13
    //26//Htoi                      把十六进制组成的字符串(包含可选的前缀0x或0X)转换为与之等价的整型值 练习2-3
    //1//InputCopy                  将输入复制到输出
    //34//Itoa                      itoa函数将数字n转换为字符串并保存到s中,itoax函数可以接收三个参数,第三个参数为最小字段宽度,在必要时应在所得结果的左边填充一定的空格 练习3-4 3-6 P52
    //33//Itob                      itob(n, s, b)将整数n转换为以b为底的数,并将转换结果以字符形式保存到字符串s中,b控制进制 练习3-5
    //3//LineCount                  行统计
    //8//OneLineOneWord             每行一个单词打印输入 练习1-12
    //9//OneLineOneWordVersionTwo   每行一个单词打印输入版本二
    //17//PrintGreatInputLine       打印长度大于80个字符的所有输入行 练习1-17
    //15//PrintTheLongestInputLine  打印最长输入行
    //14//PrintTheLongestInputLineExtern 打印最长输入行(使用外部变量版,失去通用性)
    //16//PrintTheLongestInputLineVersionTwo 打印最长输入行版本二,可以打印任意长度的输入行的长度,并尽可能多地打印文本 练习1-16
    //19//Reverse                   将字符串S中的字符顺序颠倒过来,每次颠倒一个输入行中的字符顺序 练习1-19
    //24//SignPairDetection         符号配对检测 练习1-24
    //5//SpaceSubstitution          多空格用单空格替换 练习1-9
    //27//Squeeze                   从字符串S中删除字符C
    //4//STNCount                   空格,制表符以及换行符统计 练习1-8
    //28//Strcat                    将字符串T连接到字符串S的尾部,S必须有足够大的空间
    //38//Strcmp                    strcmp函数返回值测试
    //36//Strindex                  strindex(s,t)函数返回字符串t在字符串s中的出现的开始位置或索引,当s不包含t时返回-1 练习4-1
    //29//Strpbrk                   将字符串S2中的任一字符在字符串S1中第一次出现的位置作为结果返回,如果S1中不包含S2中的字符,返回-1  练习2-5
    //35//Trim                      删除字符串尾部的空格符,制表符和换行符 P53
    //7//WordCount                  单词数行数字符数统计
//Tree          树
    ////BinaryTree          二叉树
    ////HuffmanTree         哈夫曼树
//TypeSystem    类型系统
    //DataType              数据类型
    //DetermineRanges       数据范围
    //Enum                  枚举
    //Typedef               类型定义
    //UnionType             联合
