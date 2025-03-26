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


;21.	Sa se citeasca de la tastatura un nume de fisier si un numar. 
;Sa se citeasca din fisierul dat cuvintele separate prin spatii si sa se afiseze in consola cuvintele care sunt pe pozitiile multipli de numarul citit de la tastatura.


segment data use32 class=data
cuv resb 100
n dd 0
filename resb 20
descriptor dd -1
mod_acces db 'r',0
format_nr db '%u',0
format_sir db '%s',0

segment code use32 class=code
start:
    push filename
    push format_sir
    call [scanf]
    add esp,4*2
    
    push n 
    push format_nr
    call [scanf]
    add esp,4*2
    
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    
    mov [descriptor],eax
    
    citire_cuv:
        push cuv
        push format_sir
        push dword[descriptor]
        call [fscanf]
        add esp,4*3
        cmp byte[cuv],0
        JE iesire_bucla
        
    iesire_bucla:
    
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    
    push dword 0
    call [exit]

   