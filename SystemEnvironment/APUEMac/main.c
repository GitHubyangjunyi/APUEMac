//
//  main.c
//  APUEMac
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

#define OPTSTR "vi:o:f:h"//程序推荐的命令行开关
#define USAGE_FMT  "%s [-v] [-f hexflag] [-i inputfile] [-o outputfile] [-h]"
#define ERR_FOPEN_INPUT  "fopen(input, r)"
#define ERR_FOPEN_OUTPUT "fopen(output, w)"
#define ERR_DO_THE_NEEDFUL "do_the_needful blew up"
#define DEFAULT_PROGNAME "george"

extern int errno;
extern char *optarg;
extern int opterr, optind;

typedef struct {
    int           verbose;
    uint32_t      flags;
    FILE         *input;
    FILE         *output;
} options_t;

int dumb_global_variable = -11;

//现代编译器几乎都是多遍编译器所以在生成代码之前构建一个完整的符号表因此并不严格要求使用函数原型
//总是包含一个 usage() 函数，当 main() 函数不理解你从命令行传入的内容时会调用这个函数
void usage(char *progname, int opt);
int do_the_needful(options_t *options);

int main(int argc, const char * argv[])
{
    int opt;
    options_t options = { 0, 0x0, stdin, stdout };
    opterr = 0;
    //文件前面定义的 OPTSTR 是驱动 getopt() 行为的模板。opt 变量接受 getopt() 找到的任何命令行选项的字符值，程序对检测命令行选项的响应发生在 switch 语句中
    while ((opt = getopt(argc, argv, OPTSTR)) != EOF)//核心：使用 getopt() 来遍历 argv
        switch(opt)
    {
        case 'i':
            if (!(options.input = fopen(optarg, "r")))
            {
                perror(ERR_FOPEN_INPUT);
                exit(EXIT_FAILURE);
            }
            break;
        case 'o':
            if (!(options.output = fopen(optarg, "w")))
            {
                perror(ERR_FOPEN_OUTPUT);
                exit(EXIT_FAILURE);
            }
            break;
        case 'f':
            options.flags = (uint32_t )strtoul(optarg, NULL, 16);
            break;
        case 'v':
            options.verbose += 1;
            break;
        case 'h':
        default:
            usage(basename(argv[0]), opt);
            break;
    }
    if (do_the_needful(&options) != EXIT_SUCCESS)
    {
        perror(ERR_DO_THE_NEEDFUL);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

void usage(char *progname, int opt)
{
    fprintf(stderr, USAGE_FMT, progname?progname:DEFAULT_PROGNAME);
    exit(EXIT_FAILURE);
}

int do_the_needful(options_t *options){
    if (!options)
    {
        errno = EINVAL;
        return EXIT_FAILURE;
    }
    if (!options->input || !options->output)
    {
        errno = ENOENT;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

//函数do_the_needful()接受一个指向options_t结构的指针,我验证options指针不为NULL然后继续验证input和output结构成员,如果其中一个测试失败返回EXIT_FAILURE
//并且通过将外部全局变量errno设置为常规错误代码,我可以告知调用者常规的错误原因,调用者可以使用便捷函数perror()来根据errno的值发出便于阅读的错误消息
//函数几乎总是以某种方式验证它们的输入,如果完全验证代价很大那么尝试执行一次并将验证后的数据视为不可变,usage()函数使用fprintf()调用中的条件赋值验证progname参数
//接下来usage()函数就退出了所以我不会费心设置errno也不用操心是否使用正确的程序名
//在这里我要避免的最大错误是解引用NULL指针,这将导致操作系统向我的进程发送一个名为SYSSEGV的特殊信号导致不可避免的死亡
//用户最不希望看到的是由SYSSEGV而导致的崩溃,最好是捕获NULL指针以发出更合适的错误消息并优雅地关闭程序
//有些人抱怨在函数体中有多个return语句,说些“控制流的连续性”之类的东西,老实说如果函数中间出现错误那就应该返回这个错误条件,写一大堆嵌套的if语句只有一个return绝不是一个好主意
//最后如果你编写的函数接受四个以上的参数请考虑将它们绑定到一个结构中,并传递一个指向该结构的指针,这使得函数签名更简单更容易记住并且在以后调用时不会出错
//它还可以使调用函数速度稍微快一些,因为需要复制到函数堆栈中的东西更少,在实践中只有在函数被调用数百万或数十亿次时才会考虑这个问题
//这个main()函数的目的是收集用户提供的参数执行最基本的输入验证然后将收集到的参数传递给使用它们的函数
//这个示例声明一个使用默认值初始化的options变量并解析命令行根据需要更新options
//为什么opt被声明为32位int,但是预期是8位char?事实上getopt()返回一个int,当它到达argv末尾时取负值,我会使用EOF匹配,char是有符号的,但我喜欢将变量匹配到它们的函数返回值
//v当检测到一个已知的命令行选项时会发生特定的行为,在OPTSTR中指定一个以冒号结尾的参数,这些选项可以有一个参数
//当一个选项有一个参数时,argv中的下一个字符串可以通过外部定义的变量optarg提供给程序,我使用optarg来打开文件进行读写或者将命令行参数从字符串转换为整数值
//这里有几个关于代码风格的要点:
//将opterr初始化为0禁止getopt触发?
//在main()的中间使用exit(EXIT_FAILURE);或exit(EXIT_SUCCESS);
///* NOTREACHED */是我喜欢的一个lint指令
//在返回int类型的函数末尾使用return EXIT_SUCCESS;
//显示强制转换隐式类型

//$ ./a.out -h
//a.out [-v] [-f hexflag] [-i inputfile] [-o outputfile] [-h]
//事实上在编译后usage()就会向stderr发出这样的内容
