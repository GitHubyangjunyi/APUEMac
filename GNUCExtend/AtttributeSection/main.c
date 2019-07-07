//
//  main.c
//  AtttributeSection
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    
    
    
    
    return 0;
}

//使用atttribute来声明一个section属性主要用途是在程序编译时将一个函数或变量放到指定的段,即section中
//一个可执行目标文件它主要由代码段/数据段/BSS段构成,代码段主要存放编译生成的可执行指令代码,数据段和BSS段用来存放全局变量/未初始化的全局变量
//代码段/数据段和BSS段构成了一个可执行文件的主要部分,除了这三个段,可执行文件中还包含其它一些段,用编译器的专业术语讲,还会包含其它一些section
//比如只读数据段/符号表等等,我们可以使用下面的readelf命令,去查看一个可执行文件中各个section的信息
//$ readelf -S a.out
//
//    here are 31 section headers, starting at offset 0x1848:
//Section Headers:
//    [Nr] Name                Type           Addr     Off    Size
//    [ 0]                      NULL         00000000 000000 000000
//    [ 1] .interp             PROGBITS      08048154 000154 000013
//    [ 2] .note.ABI-tag        NOTE         08048168 000168 000020
//    [ 3] .note.gnu.build-i    NOTE         08048188 000188 000024
//    [ 4] .gnu.hash            GNU_HASH     080481ac 0001ac 000020
//    [ 5] .dynsym              DYNSYM       080481cc 0001cc 000040
//    [ 6] .dynstr              STRTAB       0804820c 00020c 000045
//    [ 7] .gnu.version         VERSYM       08048252 000252 000008
//    [ 8] .gnu.version_r       VERNEED      0804825c 00025c 000020
//    [ 9] .rel.dyn             REL          0804827c 00027c 000008
//    [10] .rel.plt             REL          08048284 000284 000008
//    [11] .init                PROGBITS     0804828c 00028c 000023
//    [13] .plt.got             PROGBITS     080482d0 0002d0 000008
//    [14] .text                PROGBITS     080482e0 0002e0 000172
//    [15] .fini                PROGBITS     08048454 000454 000014
//    [16] .rodata              PROGBITS     08048468 000468 000008
//    [17] .eh_frame_hdr        PROGBITS     08048470 000470 00002c
//    [18] .eh_frame            PROGBITS     0804849c 00049c 0000c0
//    [19] .init_array          INIT_ARRAY   08049f08 000f08 000004
//    [20] .fini_array          FINI_ARRAY   08049f0c 000f0c 000004
//    [21] .jcr                 PROGBITS     08049f10 000f10 000004
//    [22] .dynamic             DYNAMIC      08049f14 000f14 0000e8
//    [23] .got                 PROGBITS     08049ffc 000ffc 000004
//    [24] .got.plt             PROGBITS     0804a000 001000 000010
//    [25] .data                PROGBITS     0804a020 001020 00004c
//    [26] .bss                 NOBITS       0804a06c 00106c 000004
//    [27] .comment             PROGBITS     00000000 00106c 000034
//    [28] .shstrtab            STRTAB       00000000 00173d 00010a
//    [29].symtab               SYMTAB       00000000 0010a0 000470
//    [30].strtab               STRTAB       00000000 001510 00022d
//
//在Linux环境下使用GCC编译生成一个可执行文件a.out,使用上面的readelf命令就可以查看这个可执行文件中各个section的基本信息
//比如大小/起始地址等等,在这些section中,其中.text section就是我们常说的代码段,.data section是数据段,.bss section是BSS段
//我们知道一段源程序代码在编译生成可执行文件的过程中函数和变量是放在不同段中的,一般默认的规则如下:
//section组成
//代码段(.text) 函数定义/程序语句
//数据段(.data) 初始化的全局变量/初始化的静态局部变量
//BSS段(.bss)    未初始化的全局变量/未初始化的静态局部变量
//比如在下面的程序中,我们分别定义一个函数/一个全局变量和一个未初始化的全局变量
////hello.c
//
//    int global_val = 8;
//    int uninit_val;
//
//    void print_star(void)
// {
//        printf("****\n");
// }
//
// int main(void)
// {
//        print_star();
//        return 0;
// }
//
//接着我们使用GCC编译这个程序,查看生成的可执行文件a.out的符号表和section header表信息
//$ readelf -S a.out
//
//符号表信息：
//    Num:  Value   Size Type    Bind   Vis      Ndx Name
//    37: 00000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
//    48: 0804a024     4 OBJECT  GLOBAL DEFAULT   26 uninit_val
//    51: 0804a014     0 NOTYPE  WEAK   DEFAULT   25 data_start
//    52: 0804a020     0 NOTYPE  GLOBAL DEFAULT   25 _edata
//    53: 080484b4     0 FUNC    GLOBAL DEFAULT   15 _fini
//    54: 0804a01c     4 OBJECT  GLOBAL DEFAULT   25 global_val
//    55: 0804a014     0 NOTYPE  GLOBAL DEFAULT   25 __data_start
//    61: 08048450    93 FUNC    GLOBAL DEFAULT   14 __libc_csu_init
//    62: 0804a028     0 NOTYPE  GLOBAL DEFAULT   26 _end
//    63: 08048310     0 FUNC    GLOBAL DEFAULT   14 _start
//    64: 080484c8     4 OBJECT  GLOBAL DEFAULT   16 _fp_hw
//    65: 0804840b    25 FUNC    GLOBAL DEFAULT   14 print_star
//    66: 0804a020     0 NOTYPE  GLOBAL DEFAULT   26 __bss_start
//    67: 08048424    36 FUNC    GLOBAL DEFAULT   14 main
//    71: 080482a8     0 FUNC    GLOBAL DEFAULT   11 _init
//    section header信息：
//    Section Headers:
//    [Nr] Name         Type        Addr     Off    Size
//    [14] .text        PROGBITS    08048310 000310 0001a2
//    [25] .data        PROGBITS    0804a014 001014 00000c
//    [26] .bss         NOBITS      0804a020 001020 000008
//    [27] .comment     PROGBITS    00000000 001020 000034
//    [28] .shstrtab    STRTAB      00000000 001722 00010a
//    [29] .symtab      SYMTAB      00000000 001054 000480
//    [30] .strtab      STRTAB      00000000 0014d4 00024e
//
//通过符号表和节头表section header table信息我们可以看到,函数print_star被放在可执行文件中的.text section,即代码段
//初始化的全局变量global_val被放在了a.out的.data section,即数据段
//而未初始化的全局变量uninit_val则被放在了.bss section,即BSS段
//编译器在编译程序时是以源文件为单位,将一个个源文件编译生成一个个目标文件,在编译过程中都会按照这个默认规则,将函数和变量分别放在不同的section中
//后将各个section组成一个目标文件,编译过程结束后链接器接着会将各个目标文件组装合并/重定位,生成一个可执行文件
//链接器是如何将各个目标文件组装成一个可执行文件的呢?
//链接器首先会分别将各个目标文件的代码段整合,组装成一个大的代码段,将各个目标文件中的数据段整合,合并成一个大的数据段
//接着将合并后的新代码段和数据段再合并为一个文件后经过重定位,就生成了一个可以运行的可执行文件了
//现在又有一个疑问来了,链接器在将各个不同的section段组装成一个可执行文件的过程中,各个section的顺序如何排放呢?
//比如代码段/数据段/BSS段/符号表等,谁放在前面?谁放在后面?
//链接器在链接过程中会将不同的section,按照链接脚本中指定的各个section的排放顺序组装成一个可执行文件
//一般在Ubuntu等PC版本的系统中会有默认的链接脚本,不需要程序员操心
//$ ld --verbose
//我们使用上面命令就可以查看编译当前程序时链接器使用的默认链接脚本
//在嵌入式系统中因为是交叉编译,所以软件源码一般会自带一个链接脚本,比如在U-boot源码的根目录下面你会看到一个u-boot.lds的文件
//这个文件就是编译U-boot时链接器要使用的链接脚本,在Linux内核中同样会有vmlinux.lds这样一个链接脚本
//
//在GNU C中我们可以通过attribute的section属性,显式指定一个函数或变量在编译时放到指定的section里面
//通过上面的程序我们知道,未初始化的全局变量是放在.data section中的,即放在BSS段中
//现在我们就可以通过section属性把这个未初始化的全局变量放到数据段.data中
//
//    int global_val = 8;
//    int uninit_val __attribute__((section(".data")));
//    int main(void)
//    {
//        return 0;
//    }
//
//有了section这个属性我们接下来就可以试着分析U-boot在启动过程中是如何将自身代码加载的RAM中的
//搞嵌入式的都知道U-boot的用途主要是加载Linux内核镜像到内存,给内核传递启动参数,然后引导Linux操作系统启动
//U-boot一般存储在Nor ﬂash或NAND Flash上,无论从Nor Flash还是从Nand Flash启动,U-boot其本身在启动过程中,也会从Flash存储介质上加载自身代码到内存
//然后进行重定位,跳到内存RAM中去执行,这个功能一般叫做自举,Uboot重定位的过程就不展开了
//我们的主要任务是去看看U-boot是怎么完成自拷贝的或者说它是怎样将自身代码从Flash拷贝到内存RAM中的
//在拷贝自身代码的过程中一个主要的疑问就是U-boot是如何识别自身代码的?是如何知道从哪里拷贝代码的?是如何知道拷贝到哪里停止的?
//这个时候我们不得不说起U-boot源码中的一个零长度数组
//    char __image_copy_start[0] __attribute__((section(".__image_copy_start")));
//    char __image_copy_end[0] __attribute__((section(".__image_copy_end")));
//
//这两行代码定义在U-boot-2016.09中的arch/arm/lib/section.c文件中,在其它版本中可能路径不同或者没有定义,建议大家可以下载U-boot-2016.09这个版本的U-boot源码
//这两行代码的作用是分别定义一个零长度数组并告诉编译器要分别放在.imagecopystart和.image_copy_end这两个section中
//链接器在链接各个目标文件时,会按照链接脚本里各个section的排列顺序将各个section组装成一个可执行文件
//U-boot的链接脚本u-boot.lds在U-boot源码的根目录下面
//
//
//
//    OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
//    OUTPUT_ARCH(arm)
//    ENTRY(_start)
//    SECTIONS
//{
//    . = 0x00000000;
//    . = ALIGN(4);
//    .text :
//    {
//        *(.__image_copy_start)
//            *(.vectors)
//            arch/arm/cpu/armv7/start.o(.text*)
//            *(.text*)
//    }
//    . = ALIGN(4);
//    .data :{
//        *(.data*)
//    }
//    ...
//    ...
//    . = ALIGN(4);
//    .image_copy_end :
//    {
//        *(.__image_copy_end)
//    }
//    .end :{
//        *(.__end)
//    }
//    _image_binary_end = .;
//    . = ALIGN(4096);
//    .mmutable :{
//        *(.mmutable)
//    }
//    .bss_start __rel_dyn_start(OVERLAY) : {
//        KEEP(*(.__bss_start));
//        __bss_base = .; }
//    .bss __bss_base(OVERLAY) : {
//        *(.bss*)
//        . = ALIGN(4);
//        __bss_limit = .; }
//    .bss_end __bss_limit(OVERLAY) : {
//        KEEP(*(.__bss_end));
//    }
//}
//
//通过链接脚本我们可以看到__image_copy_start和__image_copy_end这两个section在链接的时候分别放在了代码段.text的前面,数据段.data的后面
//作为U-boot拷贝自身代码的起始地址和结束地址,而在这两个section中,我们除了放2个零长度数组外并没有再放其它变量
//根据前面的学习我们知道,零长度数组是不占用存储空间的,所以上面定义的两个零长度数组其实就分别代表了U-boot镜像要拷贝自身镜像的起始地址和结束地址
//无论U-boot自身镜像是存储在Nor Flash还是Nand Flash上,我们只要知道了这两个地址就可以直接调用相关代码拷贝
//接着在arch/arm/lib/relocate.S中,ENTRY(relocate_code)汇编代码主要完成代码拷贝的功能
//    ENTRY(relocate_code)
//        ldr r1, =__image_copy_start /* r1 <- SRC &__image_copy_start */
//        subs    r4, r0, r1            /* r4 <- relocation offset */
//        beq relocate_done            /* skip relocation*/
//        ldr r2, =__image_copy_end    /* r2 <- SRC &__image_copy_end */
//
//    copy_loop:
//        ldmia    r1!, { r10 - r11 }    /* copy from source address [r1] */
//        stmia    r0!, { r10 - r11 }    /* copy to   target address [r0] */
//        cmp r1, r2                    /* until source end address [r2] */
//        blo copy_loop
//
//在这段汇编代码中寄存器R1和R2分别表示要拷贝镜像的起始地址和结束地址
//R0表示要拷贝到RAM中的地址,R4存放的是源地址和目的地址之间的偏移,在后面重定位过程中会用到这个偏移值
//ldr r1, =__image_copy_start
//在ARM汇编代码中的ldr指令立即寻址,直接对数组名进行引用,获取要拷贝镜像的首地址,并保存在R1寄存器中
//数组名本身其实就代表一个地址,通过这种方式U-boot在嵌入式启动的初始阶段,就完成了自身代码的拷贝工作
//从Flash上拷贝自身镜像到RAM中然后再进行重定位,然后跳到RAM中执行
