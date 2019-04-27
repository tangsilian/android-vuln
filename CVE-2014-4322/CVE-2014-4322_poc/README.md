# CVE-2014-4322_poc

poc code works on Nexus Android 4.4/5.0
Gain privileges:system -> root,as a part of  https://github.com/retme7/CVE-2014-7911_poc

author:  retme  (retme7@gmail.com)  

@returnsme on twitter & @retme on weibo

website: retme.net

The exploit must be excuted as system privilege and  several specific  SELinux  context.
If exploit successed,you will gain root privilege and "kernel" SELinux  context

# bug info
https://www.codeaurora.org/projects/security-advisories/memory-corruption-qseecom-driver-cve-2014-4322

#how to build
  ndk-build

#usage 

* Kitkat:

run  exploit as  system privilege

* Lolipop:

run  exploit as  system privilege,with SELinux context  such as "keystore","vold","drmserver","mediaserver","surfaceflinger"

If exploit successed,you will gain root privilege and "kernel" SELinux  context
