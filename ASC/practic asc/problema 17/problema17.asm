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

;17.	Sir de la tastatura cu nr de maxim 5 cifre. sa se gaseasca max si min,sa se scrie in fisier, sa se inmulteasca si rezultatul sa se pastreze in mem.
segment data use32 class=data
n dd 0
max dd 0
min dd 0FFFFFFFFh
format db '%u',0
format_afis db '%u ',0
fisier db 'output.txt',0
mod_acces db 'a',0
descriptor dd -1
rez dq 0
format_long db '%llu',0

segment code use32 class=code
start:

    bucla:
        push dword n
        push format
        call [scanf]
        add esp,4*2
        
        cmp dword[n],0
        JE iesire_bucla
        
        mov eax,dword[n]
        cmp eax,dword[min]
        JAE maxim
        mov dword[min],eax
        maxim:
            cmp eax,dword[max]
            JBE bucla
            mov dword[max],eax
            jmp bucla
            
    iesire_bucla:
    ;fopen(fisier,mod_acces)
    push mod_acces
    push fisier
    call [fopen]
    add esp,4*2
    
    cmp eax,0
    je eroare
    mov dword[descriptor],eax
    
    
    push dword [max]
    push format_afis
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    push dword [min]
    push format_afis
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    
    mov eax,[min]
    mov ebx,dword[max]
    mul ebx
    mov dword[rez+4],edx
    mov dword[rez],eax
    
    push dword[rez+4]
    push dword[rez]
    push format_long
    call [printf]
    add esp,4*3
    eroare:
    push dword 0
    call [exit]

   