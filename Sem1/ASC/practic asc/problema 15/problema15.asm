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

;15.	Sa citesti un nume de fisier de la tastatura, sa deschizi fisieru, sa numeri cate caractere is in fisier, si apoi sa pui nr ala la capatu fisierului.

segment data use32 class=data
s resb 200
len equ 200
format_nr db ' %u',0
filename resb 20
mod_acces db 'a+',0
descriptor dd -1
format_sir db '%s',0
mesaj db 'Nu s-a putut deschide fisierul',0
segment code use32 class=code
start:
    ;scanf(%s,filename)
    push filename
    push format_sir
    call [scanf]
    add esp,4*2
    
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    cmp eax,0
    je eroare_deschidere
    mov dword[descriptor],eax
    
    ;fread(s,len,descriptor)
    push dword[descriptor]
    push  dword len
    push dword 1
    push s 
    call [fread]
    add esp,4*4
    push eax
    push format_nr
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    
    push dword 0
    call [exit]
    
    eroare_deschidere:
    push mesaj
    call [printf]
    add esp,4
    
    push dword 0
    call [exit]

   