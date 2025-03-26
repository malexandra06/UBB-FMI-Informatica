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
        
;5.	Se citeste de la tastatura un sir de caractere (litere mici si litere mari, cifre, caractere speciale, etc). Sa se formeze un sir nou doar cu literele mici si un sir nou doar cu literele mari. Sa se afiseze cele 2 siruri rezultate pe ecran.

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
sir resb 100
sir_a resb 100
sir_A resb 100
format db '%s ',0

segment  code use32 class=code ; segmentul de cod
start: 
    ;gets(buffer)
    push sir
    call [gets]
    add esp,4
    
    mov esi,sir
    mov edi,sir_A
    mov ebx,sir_a
    repeta:
        lodsb
        cmp al,0
        JE iesire
        cmp al,'A'
        JB repeta
        cmp al,'z'
        JA repeta
        cmp al,'Z'
        JBE sir_mare
        cmp al,'a'
        JB repeta
        mov byte [ebx],al
        add ebx,1
        jmp repeta
        sir_mare:
            stosb
        jmp repeta
    iesire:
    push sir_A
    push format
    call [printf]
    add esp,4*2
    
    push sir_a
    push format
    call [printf]
    add esp,4*2
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului