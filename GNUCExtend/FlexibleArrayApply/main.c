//
//  main.c
//  FlexibleArrayApply
//
//  Created by 杨俊艺 on 2019/7/7.
//  Copyright © 2019 杨俊艺. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//struct urb {
//    struct kref kref;
//    void *hcpriv;
//    atomic_t use_count;
//    atomic_t reject;
//    int unlinked;
//
//    struct list_head urb_list;
//    struct list_head anchor_list;
//    struct usb_anchor *anchor;
//    struct usb_device *dev;
//    struct usb_host_endpoint *ep;
//    unsigned int pipe;
//    unsigned int stream_id;
//    int status;
//    unsigned int transfer_flags;
//    void *transfer_buffer;
//    dma_addr_t transfer_dma;
//    struct scatterlist *sg;
//    int num_mapped_sgs;
//    int num_sgs;
//    u32 transfer_buffer_length;
//    u32 actual_length;
//    unsigned char *setup_packet;
//    dma_addr_t setup_dma;
//    int start_frame;
//    int number_of_packets;
//    int interval;
//
//    int error_count;
//    void *context;
//    usb_complete_t complete;
//    struct usb_iso_packet_descriptor iso_frame_desc[0];
//};
//在这个结构体内定义了 USB 数据包的传输方向、传输地址、传输大小、传输模式等。这些细节我们不深究，我们只看后一个成员
//在URB结构体的最后定义一个零长度数组主要用于USB的同步传输
//USB有4种传输模式:中断传输/控制传输/批量传输和同步传输
//不同的USB设备对传输速度和传输数据安全性的要求不同,所采用的传输模式是不同的
//USB摄像头对视频或图像的传输实时性要求较高,对数据的丢帧不是很在意,丢一帧无所谓,接着往下传
//所以USB摄像头采用的是USB同步传输模式,现在淘宝上的USB摄像头,打开它的说明书一般会支持多种分辨率:从16*16到高清720P多种格式
//不同分辨率的视频传输对于一帧图像数据,对USB的传输数据包的大小和个数需求是不一样的,那USB到底该如何设计去适配这种不同大小的数据传输要求
//但又不影响USB的其它传输模式呢?答案就在结构体内的这个零长度数组上
//当用户设置不同的分辨率传输视频,USB就需要使用不同大小和个数的数据包来传输一帧视频数据,通过零长度数组构成的这个变长结构体就可以满足这个要求
//可以根据一帧图像数据的大小灵活地去申请内存空间满足不同大小的数据传输
//但这个零长度数组又不占用结构体的存储空间,当USB使用其它模式传输时不受任何影响,完全可以当这个零长度数组不存在,所以不得不说这样的设计真是妙!

struct buffer
{
    int len;
    int a[0];
};

struct bufferp
{
    int len;
    int *a;
};

int main(int argc, const char * argv[]) {
    
    
    printf("buffer: %d\n", sizeof(struct buffer));
    printf("bufferp: %d\n", sizeof(struct bufferp));
    
    
    
    return 0;
}

//至于为什么不使用指针来代替零长度数组?
//大家在各种场合可能常常会看到这样的字眼:数组名在作为函数参数进行参数传递时就相当于是一个指针
//在这里我们千万别被这句话迷惑了:数组名在作为函数参数传递时,确实传递的是一个地址
//但数组名绝不是指针,两者不是同一个东西
//数组名用来表征一块连续内存存储空间的地址,而指针是一个变量,编译器要给它单独再分配一个内存空间用来存放它指向的变量的地址
//对于一个指针变量编译器要为这个指针变量单独分配一个存储空间
//然后在这个存储空间上存放另一个变量的地址,我们就说这个指针指向这个变量
//而数组名编译器不会再给其分配一个存储空间的,它仅仅是一个符号,跟函数名一样用来表示一个地址
//(就是标号,学过汇编就好理解了,推荐x86汇编语言:从实模式到保护模式 李忠 著)
//我们接下来看另一个程序
////hello.c
//int array1[10] ={1,2,3,4,5,6,7,8,9};
//int array2[0];
//int *p = &array1[5];
//int main(void)
//{
//    return 0;
//}
//
//在这个程序中我们分别定义一个普通数组/一个零长度数组和一个指针变量,其中这个指针变量p的值为array1[5]这个数组元素的地址
//也就是说指针p指向arraay1[5]
//我们接着对这个程序使用arm交叉编译器进行编译并进行反汇编
//$ arm-linux-gnueabi-gcc hello.c -o a.out
//$ arm-linux-gnueabi-objdump -D a.out
//从反汇编生成的汇编代码中我们找到array1和指针变量p的汇编代码
//00021024 <array1>:
//21024:        00000001    andeq    r0, r0, r1
//21028:        00000002    andeq    r0, r0, r2
//2102c:        00000003    andeq    r0, r0, r3
//21030:        00000004    andeq    r0, r0, r4
//21034:        00000005    andeq    r0, r0, r5
//21038:        00000006    andeq    r0, r0, r6
//2103c:        00000007    andeq    r0, r0, r7
//21040:        00000008    andeq    r0, r0, r8
//21044:        00000009    andeq    r0, r0, r9
//21048:        00000000    andeq    r0, r0, r0
//0002104c <p>:
//   2104c:    00021038    andeq    r1, r2, r8, lsr r0
//    Disassembly of section .bss:
//00021050 < __bss_start > :
//    21050 :    00000000    andeq    r0, r0, r0
//
//从汇编代码中可以看到,对于长度为10的数组array1[10],编译器给它分配了从0x21024--0x21048一共40个字节的存储空间
//但并没有给数组名array1单独分配存储空间,数组名array1仅仅表示这40个连续存储空间的首地址,即数组元素array1[0]的地址
//而对于array2[0]这个零长度数组,编译器并没有给它分配存储空间,此时的array2仅仅是一个符号,用来表示内存中的某个地址
//我们可以通过查看可执行文件a.out的符号表来找到这个地址值
//$ readelf -s  a.out
//
//88: 00021024       40 OBJECT  GLOBAL DEFAULT   23 array1
//89: 00021054        0 NOTYPE    GLOBAL DEFAULT    24 _bss_end__
//90: 00021050        0 NOTYPE    GLOBAL DEFAULT    23 _edata
//91: 0002104c        4 OBJECT    GLOBAL DEFAULT    23 p
//92: 00010480        0 FUNC    GLOBAL DEFAULT        14 _fini
//93: 00021054        0 NOTYPE    GLOBAL DEFAULT    24 __bss_end__
//94: 0002101c        0 NOTYPE    GLOBAL DEFAULT    23 __data_start_
//96: 00000000        0 NOTYPE    WEAK    DEFAULT    UND __gmon_start__
//97: 00021020        0 OBJECT    GLOBAL HIDDEN    23 __dso_handle
//98: 00010488        4 OBJECT    GLOBAL DEFAULT    15 _IO_stdin_used
//99: 0001041c       96 FUNC    GLOBAL DEFAULT        13 __libc_csu_init
//100: 00021054        0 OBJECT    GLOBAL DEFAULT    24 array2
//101: 00021054        0 NOTYPE    GLOBAL DEFAULT    24 _end
//102: 000102d8        0 FUNC    GLOBAL DEFAULT        13 _start
//103: 00021054        0 NOTYPE    GLOBAL DEFAULT    24 __end__
//104: 00021050        0 NOTYPE    GLOBAL DEFAULT    24 __bss_start
//105: 000104002    8 FUNC    GLOBAL DEFAULT        13 main
//107: 00021050        0 OBJECT    GLOBAL HIDDEN    23 __TMC_END__
//110: 00010294        0 FUNC    GLOBAL DEFAULT        11 _init
//
//从符号表里可以看到array2的地址为0x21054,在程序bss段的后面
//array2符号表示的默认地址是一片未使用的内存空间仅此而已,编译器绝不会单独再给其分配一个内存空间来存储数组名
//看到这里也许你就明白了:数组名和指针并不是一回事,数组名虽然在作为函数参数时,可以当一个地址使用,但是两者不能划等号
//菜刀有时候可以当武器用,但是你不能说菜刀就是武器,至于为什么不用指针,很简单,使用指针的话,指针本身也会占用存储空间不说
//根据上面的USB驱动的案例分析你会发现,它远远没有零长度数组用得巧妙——不会对结构体定义造成冗余,而且使用起来也很方便
