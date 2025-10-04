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
;7.	Se da un sir de qword definit in data segment. elementele sirului sunt in baza 16
;a)	sa se printeze bytes care compun qword urile din sir
;b) sa se identifice words care au ultima cifra egala cu constanta k definita in segmentul de date. sa se salveze aceste words in sirul d
;c)	sa se identifice dwords care sunt cuprinse in intervalul AAA - FFFF. sa se determine numarul dwords din acest interval. sa se afiseze acest numar in baza 10 in fisierul 'iesire.txt'

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
s dq 1122334455h,2433h,4815h,829h,4326786639h
lenb equ $-s
lenw equ ($-s)/2
lend equ ($-s)/4
format db '%x ',0
spatiu db 0x0A,0
d resw 100
k equ 5h
filename db 'iesire.txt',0
mod_acces db 'w',0
descriptor dd -1
segment  code use32 class=code ; segmentul de cod
start: 
    mov esi,s
    mov ecx,lenb
    JECXZ final1
    cld
    bucla_afis:
    mov eax,0
    lodsb
    push ecx
    push eax
    push format
    call [printf]
    add esp,4*2
    pop ecx
    loop bucla_afis
    final1:
    mov esi,s
    mov ecx,lenw
    mov edi,d
    cld
    JECXZ final2
    bucla_sir:
    lodsw
    mov bx,ax
    and bl,1111b
    cmp bl,k
    JNE final_b
    stosw
    final_b:
    loop bucla_sir
    final2:
    mov esi,s
    cld
    mov ecx,lend
    mov edx,0
    bucla_d:
    lodsd
    cmp eax,0AAAh
    JB ies
    cmp eax,0FFFFh
    JA ies
    inc edx
    ies:
    loop bucla_d
    push edx
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    cmp eax,0
    JE final3
    mov dword[descriptor],eax
    ;fprintf(descriptor,format,nr)
    pop edx
    push edx
    push dword format
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    final3:
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului