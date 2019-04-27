#!/bin/sh
if [ "$1" == "32" ]; then
	nasm -o /dev/stdout shellcode-32.s | msfencode4.0 -t c -e generic/none -b '\x00' > harness.c && echo "void main() { (*(void(*)())buf)(); }" >> harness.c && gcc -m32 -fno-stack-protector -z execstack -o harness harness.c && ./harness
else
	nasm -o /dev/stdout shellcode-64.s | msfencode4.0 -t c -e generic/none -b '\x00' > harness.c && echo "void main() { (*(void(*)())buf)(); }" >> harness.c && gcc -fno-stack-protector -z execstack -o harness harness.c && ./harness
fi
