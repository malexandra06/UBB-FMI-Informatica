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




segment data use32 class=data

caract dd 0
n dd 0
sir resb 200
cuv resb 200
format_ch db '%c ',0
format_nr db '%u',0
format_sir db '%s',0
filename1 resb 100
mod_read db 'r',0
mod_write db 'w',0
filename2 db 'output.txt',0
descriptor1 dd -1
descriptor2 dd -1

segment code use32 class=code
start:
    push filename1
    push format_sir
    call [scanf]
    add esp,4*2
    
    push caract
    push format_ch
    call [scanf]
    add esp,4*2
    
    push n
    push format_nr
    call [scanf]
    add esp,4*2
    
    ;fopen(filename1,mod_read)
    push mod_read
    push filename1
    call [fopen]
    add esp,4*2
    
    mov [descriptor1],eax
    
    ;fread(text,1,count,descriptor1)
    push dword[descriptor1]
    push 200
    push 1
    push sir
    call [fread]
    add esp,4*4
    
    mov ecx,eax
    mov esi,sir
    parcurgere:
        mov edi,cuv
        mov ebx,0
        lodsb
        cmp al,' '
        JE final
        stosb
        inc ebx
    final:
    loop parcurgere
    
    ;fclose(descriptor1)
    push dword[descriptor1]
    call [fclose]
    add esp,4
    
    push dword 0
    call [exit]
    
    