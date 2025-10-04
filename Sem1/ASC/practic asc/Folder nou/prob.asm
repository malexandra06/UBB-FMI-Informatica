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
import getchar msvcrt.dll
extern printf, exit, scanf, fopen, fscanf, fclose, fprintf, gets,fread,getchar




segment data use32 class=data

caracter dd 0
sir resb 100
format_ch db '%c',0
file db 'output.txt',0
mod_acces db 'a',0
descriptor dd -1
format_afis db '%s',0

len dd 0
segment code use32 class=code
start:
    push sir
    call read
    
    mov [len],ebx
    push sir 
    push dword [len]
    call sortare
    
    push sir
    push format_afis
    call [printf]
        add esp,4*2
    
    push mod_acces
    push file
    call [fopen]
    add esp,4*2
    
    mov [descriptor],eax
    
    push sir 
    push format_afis
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    push dword[descriptor]
    call [fclose]
    add esp,4
    push dword 0
    call [exit]

    
    sortare:
        mov ecx,[esp+4]
        dec ecx
        mov esi,[esp+8]
        MOV EBX,1
        parcurgere:
            lodsb
            cmp al,byte[esi]
            JBE jos
            mov dl,byte[esi]
            mov [esi-1],dl
            mov [esi],al
            mov ebx,0
            jos:
            loop parcurgere
            CMP EBX,1
            JNE sortare
        ret 4*2
    
    read:
    mov edi,[esp+4]
    mov ebx,0
    cld
    citire:
        ;scanf(%c,caracter)
        push caracter
        push format_ch
        call [scanf]
        add esp,4*2
        
        ;call [getchar]
        cmp byte[caracter],'!'
        JE iesire_bucla
        
        mov al,byte[caracter]
        sub byte[caracter],'0'
        test byte[caracter],1
        JNZ citire
        inc ebx
        stosb
        JMP citire
  
    iesire_bucla:
    ret 4