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

n dd 0
format db '%c',0
sir resb 100
filename db 'result.txt',0
mod_acces db 'w',0
descriptor dd -1
format_sir db '%s',0
segment code use32 class=code
start:
    mov edi,sir
    mov ecx,0
    mov ebx,0
    citire:
        push ecx
        push n
        push format
        call [scanf]
        add esp,4*2
        
        pop ecx
        cmp byte[n],'!'
        JE iesire
        cmp byte[n],' '
        JE citire
        cmp byte[n],10
        JE citire
        test byte[n],1
        JZ citire
        mov al,byte[n]
        mov edi,sir
        jecxz true
        parcurgere:
            scasb
            JE jos
        loop parcurgere
        true:
        stosb
        inc ebx
        jos:
            mov ecx,ebx
            JMP citire
    
    iesire:
    push ecx
    push sir
    call sortare
    add esp,4*2
    
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    mov [descriptor],eax
    
    push sir
    push format_sir
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    push dword[descriptor]
    call [fclose]
    add esp,4 
    push dword 0
    call [exit]
    
    sortare:
        mov esi,[esp+4]
        
        mov ecx,[esp+8]
        dec ecx
            mov ebx,1
            bucla:
                lodsb
                cmp al,byte[esi]
                JA ok
                mov dl,byte[esi]
                mov byte[esi-1],dl
                mov byte[esi],al
                mov ebx,0
                ok:
            loop bucla
            cmp ebx,0
            JZ sortare
    ret