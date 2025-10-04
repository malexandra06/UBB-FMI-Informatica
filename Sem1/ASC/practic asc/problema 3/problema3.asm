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
        
;3.	Se citeste o propozitie de la tastatura. Sa se inverseze fiecare cuvant si sa se afiseze pe ecran.        

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
sir resb 100
inv resb 100
format db '%s',0
segment  code use32 class=code ; segmentul de cod
start: 
    ;gets(buffer)
    push sir
    call [gets]
    add esp,4
    cld
    mov ecx,0
    mov esi,sir
    mov edi,inv
    repeta:
        lodsb
        cmp al,' '
        JE next_cuv
        cmp al,0
        JE iesire
        add ecx,1
        JMP repeta
    next_cuv:
        mov ebx,esi
        push ebx
        dec esi
        dec esi
        std
        copie:
            lodsb
            cld
            stosb
            std
        loop copie
        cld
        mov byte [edi],' '
        inc edi
        pop esi
        mov ecx,0
        JMP repeta
    iesire:
        dec esi
        dec esi
        std
        ultim:
            lodsb
            cld
            stosb
            std
        loop ultim
    push inv
    push format
    call [printf]
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului