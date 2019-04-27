
Congratulations, you Got Root!



Android kernel exploit
=================


[Zimperlich](#zimperlich)
[CVE-2009-2692(Wunderbar/asroot)](#cve-2009-2692wunderbarasroot)
[RageAgainstTheCage(adbd setuid)](#rageagainstthecageadbd-setuid)
[CVE-2009-1185 Exploid](#cve-2009-1185-exploid)
[CVE-2009-2692(Wunderbar/asroot)](#cve-2009-2692wunderbarasroot-1)
[CVE-2011-1149  KillingInTheNameOf](#cve-2011-1149--killinginthenameof)
[CVE-2011-1823(GingerBreak)](#cve-2011-1823gingerbreak)
[CVE-2011-3874(zergRush)](#cve-2011-3874zergrush)
[CVE-2011-1823(GingerBreak)](#cve-2011-1823gingerbreak-1)
[Exynos-abuse](#exynos-abuse)
[CVE-2012-0056(mempodroid)](#cve-2012-0056mempodroid)
[CVE-2012-4220(diag)](#cve-2012-4220diag)
[CVE-2012-6422 exynos-mem](#cve-2012-6422-exynos-mem)
[CVE-2013-2094(linux kernel3.8.9之前开启了PERF_EVENT的设备)](#cve-2013-2094linux-kernel389之前开启了perf_event的设备)
[CVE-2013-2595](#cve-2013-2595)
[CVE-2013-6282](#cve-2013-6282)
[CVE-2013-6123](#cve-2013-6123)
[CVE-2013-6282](#cve-2013-6282-1)
[CVE-2013-6774](#cve-2013-6774)
[CVE-2014-0196](#cve-2014-0196)
[CVE-2014-2273](#cve-2014-2273)
[CVE-2014-3153](#cve-2014-3153)
[CVE-2014-4321](#cve-2014-4321)
[CVE-2014-4322](#cve-2014-4322)
[CVE-2014-4323](#cve-2014-4323)
[CVE-2014-4324](#cve-2014-4324)
[CVE-2014-7911 CVE-2014-4322 配套使用的root](#cve-2014-7911-cve-2014-4322-配套使用的root)
[CVE-2014-0975 CVE-2014-0976](#cve-2014-0975-cve-2014-0976)
[CVE-2014-9322](#cve-2014-9322)
[CVE-2015-0569](#cve-2015-0569)
[CVE-2015-1805](#cve-2015-1805)
[CVE-2015-3636](#cve-2015-3636)
[CVE-2016-2434](#cve-2016-2434)
[CVE-2016-2443](#cve-2016-2443)
[CVE-2016-3842](#cve-2016-3842)
[CVE-2016-3935 CVE-2016-6738](#cve-2016-3935-cve-2016-6738)
[CVE-2016-5195](#cve-2016-5195)
[CVE-2016-5342](#cve-2016-5342)
[CVE-2017-8890](#cve-2017-8890)
[SVE-2017-10086](#sve-2017-10086)
[CVE-2017-10661](#cve-2017-10661)




### 0x00 常见内核漏洞分析


#### Zimperlich
与RageAgainstTheCage原理类似,不一样的是此处依赖的zygote进程的降权.所有的android应用是由Zygote进程fork分支后启动的.Zygote是由root权限运行的.在fork之后新的进程将使用setuid调用降权至目标应用的uid.Android2.2以及之前版本的Zygote没有对降权时setuid调用的返回值进行检查.同样,在耗尽目标程序uid的最大进程数之后,Zygote就无法降低它的权限,然后就以root权限启动应用了.



#### CVE-2009-2692(Wunderbar/asroot)
sock_sendpage()的空指针解引用.因为sock_sendpage 没有对 socket_file_ops 结构的 sendpage 字段做指针检查,有些模块不具备sendpage 功能,初始时赋为 NULL,这样,没有做检查的sock_sendpage 有可能直接调用空指针而导致出错并提升权限.

#### RageAgainstTheCage(adbd setuid)
ADB守护进程(adbd进程)以root权限开始启动,然后降权到shell用户.在Android2.2及以前的版本中,ADB守护进程在降权时不会检查setuid调用的返回值.在此之前,adb.c中的代码都是以root权限运行,以完成部分初始化工作.通过调用setuid()将用户从root切换回shell,但setuid()在shell用户进程数达到上限RLIMIT_NPROC时,会失败,因此adb.c继续以root身份运行,而没有报错.

#### CVE-2009-1185 Exploid
CVE-2009-1185 影响android2.1及之前版本,此exploit基于udev漏洞CVE-2009-1185,udev是一个android组件负责USB连接,进程应该只处理kernel发送的device的NETLINK的socket消息，但实际上并未检测NETLINK的socket消息的来源,这样可以广播add device的socket信息,触发硬件处理事件,将恶意代码传入kernel,由其写入设备文件.这样,攻击者只需发送一条构造好的udev消息就可以提权了.

#### CVE-2009-2692(Wunderbar/asroot)
sock_sendpage()的空指针解引用.因为sock_sendpage 没有对 socket_file_ops 结构的 sendpage 字段做指针检查,有些模块不具备sendpage 功能,初始时赋为 NULL,这样,没有做检查的sock_sendpage 有可能直接调用空指针而导致出错并提升权限.


#### CVE-2011-1149  KillingInTheNameOf
CVE-2011-1149 此expolit利用了ashmem (the shared memory manager) 接口漏洞,用于修改ro.secure的值,ro.secure决定了设备的root状态.Android 的共享内存(Ashmem)子系统是一个共享内存分配器.共享内存可以通过 mmap 或者文件 I/O 进行访问.在android 2.3之前,ashmem 允许任何用户重新映射属于 init 进程的共享内存,将包括系统属性地地址空间的内存进行共享,KillingInTheNameOf 利用程序将系统属性空间重新映射为可写,并将 ro.secure 属性设置为0.在重启 adbd 后,ro.secure 属性的修改会允许 adb shell 取得 root 权限访问.

#### CVE-2011-1823(GingerBreak)
在Android 3.0版本和2.3.4之前的2.x版本上的volume守护进程(vold)由于信任从PF_NETLINK套接字接收到的消息,因此允许以root权限执行任意代码,利用方法是通过一个负数索引绕过只针对最大值的有符号整数检测.CVE-2011-1823,此exploit利用vold的漏洞,原理类似上一个.(android并没有实现linux的udev，其功能由vold进程实现，其包含VolumeManager，NetlinkManager，CommandListener等modules).Android 2.3.4之前版本的 volume 守护进程(vold)由于信任从 PF_NETLINK socket 接收到的消息,因此允许以 root 权限执行任意代码,利用方法是通过一个负数索引绕过指针对最大值的有符号整数检查.

#### CVE-2011-3874(zergRush)
漏洞的本质是"use after free".具有root权限的vold进程使用了libsysutils.so,其中某个函数存在栈溢出的问题,因此可以控制root身份的vold执行system(),借以提权.



#### CVE-2011-1823(GingerBreak)
在Android 3.0版本和2.3.4之前的2.x版本上的volume守护进程(vold)由于信任从PF_NETLINK套接字接收到的消息,因此允许以root权限执行任意代码,利用方法是通过一个负数索引绕过只针对最大值的有符号整数检测.

#### Exynos-abuse 
早期的三星手机,经常是某些设备被chmod 755/666,造成了全局可读写,然后只要将这些设备mmap出来,就可以操作物理内存,之后可以通过patch相关参数或者构造payload函数达到提权的目的.

#### CVE-2012-0056(mempodroid)
Linux通过一个特殊字符设备/proc/$pid/mem把每个进程的虚拟内存暴露为一个文件.出于安全考虑,读写这个文件的权限被严格限制,拥有写入权限的只有内存的所属进程.但是攻击者可以打开目标进程的mem设备,把它复制到进程的stdout和stderr.当stdout重定向到与虚拟内存相关的字符设备时,攻击者可以写入其他程序内存,但是写入的地址是未知的.

#### CVE-2012-4220(diag)
Android 2.3-4.2使用的QualcommInnovation Center (QuIC) Diagnostics内核模式驱动程序diagchar_core.c在实现上存在整数溢出漏洞,通过向diagchar_ioctl内传递特制的输入,远程攻击者可利用此漏洞执行任意代码或造成拒绝服务.

#### CVE-2012-6422 exynos-mem
mmap类的漏洞利用  patch syscall
https://www.cnblogs.com/gm-201705/p/9863995.html

####  CVE-2013-2094(linux kernel3.8.9之前开启了PERF_EVENT的设备)
利用该漏洞，通过perf_event_open系统调用，本地用户可以获得系统的最高权限。

#### CVE-2013-2595
/dev/msm_camera/config0高通设备MMAP漏洞。  framaroot
[exp](https://github.com/fi01/libmsm_cameraconfig_exploit/blob/master/msm_cameraconfig.c)

#### CVE-2013-6282
ARM v6/v7架构的Linux内核中的get_user/put_user接口没有验证目标地址,由于硬件架构的更迭,get_user/put_user最初用于实现和控制域切换的功能被弃用了,导致任何使用该API的内核代码都可能存在安全隐患.让任意应用来读写内核内存,造成权限泄漏.



#### CVE-2013-6123
用户态与驱动数据交换导致的任意地址写漏洞，Qualcomm平台上的copy_from_user类漏洞

#### CVE-2013-6282
ARM v6/v7架构的Linux内核中的get_user/put_user接口没有验证目标地址,由于硬件架构的更迭,get_user/put_user最初用于实现和控制域切换的功能被弃用了,导致任何使用该API的内核代码都可能存在安全隐患.让任意应用来读写内核内存,造成权限泄漏.

#### CVE-2013-6774


#### CVE-2014-0196
n_tty_write函数没有加锁,导致同步状态下出现条件竞争的漏洞.隐藏五年的提权漏洞
https://blog.csdn.net/py_panyu/article/details/45565449

#### CVE-2014-2273
发现P2的解码器驱动程序允许任何应用程序读取或写入任意存储器地址


#### CVE-2014-3153
漏洞利用了 futex_requeue,futex_lock_pi,futex_wait_requeue_pi三个函数存在的RELOCK漏洞和REQUEUE漏洞,造成了对内核栈上的数据修改,知名root工具towelroot就是利用了这个漏洞可以覆盖2014年6月以前的设备.

#### CVE-2014-4321
[CVE-2016-2431 - The Qualcomm TrustZone component in Android before 2016-05-01 on Nexus 5, Nexus 6, Nexus 7 (2013), and Android One devices allows attackers to gain privileges via a crafted application, aka internal bug 24968809](qualcomm/CVE-2016-2431)

#### CVE-2014-4322
[CVE-2014-4322-qseecom内存破坏漏洞分析](http://ele7enxxh.com/Memory-Corruption-Qseecom-Driver-CVE-2014-4322-Analysis.html)


#### CVE-2014-4323
Linux内核3.x的MDP显示驱动程序中的[drivers / video / msm / mdp.c](https://bbs.pediy.com/thread-248498.htm)中的mdp_lut_hw_update函数，用于Qualcomm Innovation Center（QuIC）Android对MSM设备和其他产品的贡献，不会验证某些启动和ioctl调用中的长度值，允许攻击者通过精心设计的应用程序获得权限提升。

#### CVE-2014-4324


#### CVE-2014-7911 CVE-2014-4322 配套使用的root
相较于media权限，以system权限执行的system_server更是攻击者觊觎的一个目标，CVE-2014-7911就是通过第三方软件准备的数据使得system_server进程执行任意代码，获取system权限后，更多的攻击目标会被暴露在外，例如使用Qualcomm一系列芯片的手机上存在的CVE-2014-4322漏洞，在正常的情况下，第三方软件是无法与其相关的驱动做交互。然而，利用CVE-2014-7911提升到system权限后，CVE-2014-4322相关的设备文件就能被打开，进而造成有效的攻击。 

http://blog.csdn.net/omnispace/article/details/52739001
system权限提权，并执行任意代码
https://researchcenter.paloaltonetworks.com/2015/01/cve-2014-7911-deep-dive-analysis-android-system-service-vulnerability-exploitation/


#### CVE-2014-0975 CVE-2014-0976

Multiple Issues in Camera Drivers
https://www.codeaurora.org/projects/security-advisories/hall-of-fame

#### CVE-2014-9322
https://hardenedlinux.github.io/system-security/2015/07/05/badiret-analysis.html


#### CVE-2015-0569
https://bbs.pediy.com/thread-208066.htm
函数进行拷贝时没有对长度进行判断，导致用户可以修改内核栈中值。


#### CVE-2015-1805
在linux 内核3.16版本之前的fs/pipe.c当中,由于pipe_read和pipe_write没有考虑到拷贝过程中数据没有同步的一些临界情况,造成了拷贝越界的问题,因此有可能导致系统crash以及系统权限提升.这种漏洞又称之为” I/O vector array overrun”

#### CVE-2015-3636
pingpong该漏洞是Linux kernel的ping套接字上存在的一个Use-After-Free漏洞。
https://github.com/fi01/CVE-2015-3636  32位

[cve-2015-6620学习总结](https://bbs.pediy.com/thread-226699.htm)

#### CVE-2016-2434
Android 2016-05-01版本，NVIDIA Video Driver存在权限提升漏洞，攻击者通过构造的应用，可获取提升的权限。


#### CVE-2016-2443
Qualcomm MSM debugfs内核任意地址写入漏洞分析  
https://www.freebuf.com/vuls/103583.html

#### CVE-2016-3842
[危害9亿安卓设备高通漏洞细节曝光（CVE-2016-3842,含POC）](http://www.hackdig.com/08/hack-38388.htm)
[实现CVE-2016-3842的堆喷](https://bbs.pediy.com/thread-218194.htm)

#### CVE-2016-3935 CVE-2016-6738
CVE-2016-3935 和 CVE-2016-6738 是我们发现的高通加解密引擎（Qualcomm crypto engine）的两个提权漏洞
通过漏洞信息，可以知道这个漏洞影响范围非常广，包括Linux Kernel 4.10.15之前的所有内核版本。
这个漏洞同时存在于Android Kernel中，在实际测试中，不需要任何权限即可造成double free导致系统崩溃。
https://github.com/jiayy/android_vuln_poc-exp/tree/master/EXP-CVE-2016-3935
https://paper.seebug.org/372/


#### CVE-2016-5195
CVE-2016-5195脏牛（Dirty COW）低权限用户利用该漏洞技术可以在全版本Linux系统上实现本地提权  
Linux内核的内存子系统在处理写时拷贝（Copy-on-Write)时存在条件竞争漏洞，导致可以破坏私有只读内存映射。一个低权限的本地用户能够利用此漏洞获取其他只读内存映射的写权限，有可能进一步导致提权漏洞。

#### CVE-2016-5342 
[CVE-2016-5342 - Heap-based buffer overflow in the wcnss_wlan_write function](qualcomm/CVE-2016-5342)

#### CVE-2017-8890
条件竞争漏洞: https://bbs.pediy.com/thread-249193.htm
[CVE-2017-8890 深度分析](https://bbs.pediy.com/thread-226057.htm)

#### SVE-2017-10086* [SVE-2017-10086 - PoC exploit for arbitrary file read/write in locked Samsung Android device via MTP](samsung/SVE-2017-10086)


#### CVE-2017-10661

[链表游戏：CVE-2017-10661之完全利用](https://www.anquanke.com/post/id/129468#h2-3)




参考：
https://blog.csdn.net/py_panyu/article/details/46045295

