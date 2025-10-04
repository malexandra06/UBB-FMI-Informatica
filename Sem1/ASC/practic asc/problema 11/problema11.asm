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
extern printf, exit, scanf, fopen, fscanf, fclose, fprintf, gets

;Se citesc cuvinte de la tastatura, sa se creeze un fisier cu numele primului .txt si restul sa se afiseze in acest fisier cu literele inversate
segment data use32 class=data
s resb 100
inv resb 100
filename resb 10
mod_acces db 'a',0
descriptor dd -1
format db '%s',0
space db 0x0A,0
segment code use32 class=code
start:
    push dword filename
    call [gets]
    add esp,4
    mov edi,filename
    bucla:
        cmp byte[edi],0
        JE iesi
        inc edi
        jmp bucla
    iesi:
    mov al,'.'
    stosb
    mov al,'t'
    stosb
    mov al,'x'
    stosb
    mov al,'t'
    stosb
    mov byte[edi],0
    
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    cmp eax,0
    JE eroare
    mov [descriptor],eax
    
    citire:
        push s
        call [gets]
        add esp,4
        
        cmp byte[s],0
        je afara
        mov esi,s
        mov ecx,0
        parcurgere:
            lodsb
            inc ecx
            cmp al,0
            JE afara_b
            JMP parcurgere
        afara_b:
            sub esi,2
            dec ecx
            mov edi,inv
            inversare:
                mov al,[esi]
                dec esi
                mov byte[edi],al
                inc edi
            loop inversare
         
            mov byte[edi],0
            push inv
            push format
            push dword[descriptor]
            call [fprintf]
            add esp,4*3
            
            push space
            push format
            push dword[descriptor]
            call[fprintf]
            add esp,4*3
            
            Jmp bucla
    afara:
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    eroare:
    push dword 0
    call [exit]
