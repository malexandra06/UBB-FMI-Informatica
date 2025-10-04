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
        
;4.	Se citeste o propozitie de la tastatura. Sa se numere literele din fiecare cuvant si sa se afiseze aceste numere pe ecran.       

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
sir resb 100
format db '%u ',0

segment  code use32 class=code ; segmentul de cod
start: 
    ;gets(buffer)
    push sir
    call [gets]
    add esp,4
    
    mov esi,sir
    mov ecx,0
    repeta:
        lodsb
        cmp al,0
        je iesire
        cmp al,' '
        je afisare
        add ecx,1
        JMP repeta
    afisare:
        push ecx
        push format
        call [printf]
        add esp,4*2
        mov ecx,0
        JMP repeta
    iesire:
        push ecx
        push format
        call [printf]
        add esp,4*2
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului