bits 32 ;asamblare si compilare pentru arhitectura de 32 biti
; definim punctul de intrare in programul principal
global  start 
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import gets msvcrt.dll
import exit msvcrt.dll
extern printf, exit,scanf,fopen,fscanf,fclose,fprintf,gets
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante

;8.	Citesc string tastatura, creem fisier string.txt, adaugam in fisier prima data majusculele apoi minusculele invers de cum apar in sir.

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
s resb 100
sir_M resb 100
sir_m resb 100
filename db 'string2.txt',0
mod_acces db 'w',0
format db '%s',0
spatiu db 0x0A, 0
descriptor dd -1
mesaj db 'EROARE',0
segment  code use32 class=code ; segmentul de cod
start: 
    ;gets(buffer)
    push s
    call [gets]
    add esp,4*1
    
    mov esi,s
    inv:
        lodsb
        cmp al,0
        je ies
        jmp inv
    ies:
    sub esi,2
    mov edi,sir_M
    mov ebx,sir_m
    bucla:
        std
        lodsb
        cmp AL,0
        JE final
        cmp AL,'A'
        JB bucla
        cmp AL,'z'
        JA bucla
        cmp AL,'Z'
        JBE majuscula
        cmp AL,'a'
        JB bucla
        minuscula:
            mov byte[ebx],AL
            inc ebx
            JMP bucla
        majuscula:
            cld
            stosb
            JMP bucla
    final:
    mov byte [edi],0
    mov byte [ebx],0
    push sir_M
call [printf]
add esp, 4
push sir_m
call [printf]
add esp, 4

    ;fopen(filename,mod_acces)
    push dword mod_acces
    push dword filename
    call [fopen]
    add esp,4*2
    
    cmp EAX,0
    JE eroare_fisier
    mov [descriptor],eax
    
    push sir_M
    push format
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    push spatiu
    push format
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    push sir_m
    push format
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4*1
    
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului
    
    eroare_fisier:
    push mesaj
    call [printf]
    add esp,4
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului
    