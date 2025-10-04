bits 32
global start 
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import gets msvcrt.dll
import exit msvcrt.dll
import fread msvcrt.dll
extern printf, exit, scanf, fopen, fscanf, fclose, fprintf, gets,fread

;18.	Se citeste un sir din input.txt. sa se afiseze invers.
segment data use32 class=data
s resb 200
inv resb 200
filename db 'input.txt',0
mod_acces db 'r',0
format db '%s',0
descriptor dd -1
len equ 200
segment code use32 class=code
start:
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    mov dword[descriptor],eax
    
    push dword[descriptor]
    push len
    push 1
    push s 
    call [fread]
    add esp,4*4
    push dword[descriptor]
    call [fclose]
    add esp,4
    mov esi,s 
    mov byte[esi+eax],0
    add esi,eax
    dec esi
    std
    mov edi,inv
    mov ecx,eax
    bucla:
    std
    lodsb
    cld
    stosb
    loop bucla
    mov byte[edi],0
    
    push inv
    call [printf]
    add esp,4
    
    
    push dword 0
    call [exit]

   