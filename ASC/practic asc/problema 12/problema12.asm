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



;Se citesc 3 numere din fisier. sa se afiseze inmultirea lor pe ecran.
segment data use32 class=data
a dd 0
b dd 0
c dd 0
format db '%d',0
filename db 'in.txt',0
mod_acces db 'r',0
descriptor dd -1
format_quad db '%lld',0
mesaj_eroare db 'Fisierul nu a putut fi deschis',0
mesaj db 'Rezultatul este '
segment code use32 class=code
start:
    ;fopen(filename,mod_acces)
    push dword mod_acces
    push dword filename
    call [fopen]
    add esp,4*2
    
    cmp EAX,0
    je eroare_fisier
    mov [descriptor],eax
    
    ;fscanf(descriptor,format,&a)
    push a
    push format
    push dword[descriptor]
    call [fscanf]
    add esp,4*3
    
    push b
    push format
    push dword[descriptor]
    call [fscanf]
    add esp,4*3
    
    push c
    push format
    push dword[descriptor]
    call [fscanf]
    add esp,4*3
    
    push dword [c]
    push dword [b]
    push dword [a]
    call inmultire
    
    push edx
    push eax
    push mesaj
    call [printf]
    add esp,4
    
    pop eax
    pop edx
    
    push eax
    push edx
    push format_quad
    call [printf]
    add esp,4*3
    
    push dword 0
    call [exit]
    
    eroare_fisier:
        push dword mesaj_eroare
        call [printf]
        add esp,4
    push dword 0
    call [exit]

   inmultire:
    mov eax,[esp+4]
    mov ebx,[esp+8]
    imul ebx
    mov ebx,[esp+12]
    imul ebx
    ret 4*3