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

;Se citeste de la tastatura m,n apoi m numere zecimale, pe linii diferite. Sa se afiseze nr cu cel putin n cifre pare in output.txt.
segment data use32 class=data
m dd 0
n dd 0
a dd 0
filename db 'output.txt',0
mod_acces db 'a',0
descriptor dd -1
format db '%u',0
nr db 0
segment code use32 class=code
start:
    push dword m
    push format
    call [scanf]
    add esp, 4*2
    
    push dword n
    push format
    call [scanf]
    add esp,4*2
    
    ;fopen(filename,mod_acces)
    push dword mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    cmp eax,0
    je eroare
    mov dword[descriptor],eax
    
    mov ecx,[m]
    bucla:
        mov dword [nr],0
        push ecx
        ;scanf(format,a)
        push a
        push format
        call [scanf]
        add esp,4*2
        mov ebx,10
        mov eax,[a]
        pop ecx
        cifre:
            cmp eax,0
            JE ies1
            mov edx,0
            div ebx
            test edx,1
            JNZ cifre
            inc byte[nr]
            JMP cifre
        ies1:
            mov edx,0
            mov dl,[nr]
            cmp edx,dword [n]
            JNE ies
            push ecx
            push dword [a]
            push format
            push dword[descriptor]
            call [fprintf]
            add esp,4*3
            pop ecx
        ies:
    loop bucla
    push dword [descriptor]
    call [fclose]
    add esp,4
    eroare:
    push dword 0
    call [exit]
