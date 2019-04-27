arm-linux-gnueabi-gcc -c shellcode.S -o shellcode
arm-linux-gnueabi-objcopy -O binary shellcode shellcode.bin	
arm-linux-gnueabi-objdump -d shellcode
