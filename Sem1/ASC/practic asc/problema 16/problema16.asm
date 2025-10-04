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

;16.	Se citesc nr din fisier, sa se faca suma nr mai mici decat 8 si sa se afiseze pe ecran.
segment data use32 class=data

n dd 0
format db '%u',0
filename db 'input.txt',0
descriptor dd -1
mod_acces db 'r',0
mesaj db 'Eroare...',0
segment code use32 class=code
start:
    
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    cmp eax,0
    je eroare_deschidere
    mov [descriptor],eax
    
    mov ebx,0
    citire:
        ;fscanf(descriptor,format,n)
        push n 
        push format
        push dword[descriptor]
        call [fscanf]
        add esp,4*3
        
        cmp dword[n],-1
        JE iesi
        cmp dword[n],8
        JA citire
        add ebx,dword[n]
        JMP citire
    iesi:
    push ebx
    push format
    call [printf]
    add esp,4*2
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

   