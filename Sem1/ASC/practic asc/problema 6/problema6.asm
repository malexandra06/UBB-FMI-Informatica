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
        
;6.	Se citesc din fisierul numere.txt mai multe numere (pare si impare). Sa se creeze 2 siruri rezultat N si P astfel: N - doar numere impare si P - doar numere pare. Afisati cele 2 siruri rezultate pe ecran.

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
a dd 0
N resd 100
P resd 100
filename db 'numere.txt',0
mod_acces db 'r',0
descriptor dd -1
mesaj db 'Eroare la citirea din fisier',0
format_citire db '%u ',0
spatiu db 0x0A, 0
segment  code use32 class=code ; segmentul de cod
start: 
    ;fopen(filename,mod_acces)
    push dword mod_acces
    push dword filename
    call [fopen]
    add esp,4*2
    cmp EAX,0
    JE eroare
    mov [descriptor],EAX
    mov esi,N
    mov edi,P
    mov ecx,0
    mov edx,0
    repeta:
    ;fscanf(descriptor,format_citire,a)
    push esi
    push edi
    push ecx
    push edx
    push a
    push format_citire
    push dword[descriptor]
    call [fscanf]
    add esp,4*3
    pop edx
    pop ecx
    pop edi
    pop esi
    cmp eax,1
    JNE iesire
    mov ebx,[a]
    test ebx,1
    JZ par
    mov dword[esi],ebx
    add esi,4
    inc ecx
    jmp repeta
    par:
    mov dword[edi],ebx
    add edi,4
    inc edx
    JMP repeta
    
iesire:
;fclose(descriptor)
    push edx
    push ecx
    push dword [descriptor]
    call [fclose]
    add esp,4
    
    mov esi,N
    pop ecx
    afisare_imp:
    lodsd
    push ecx
    push esi
    push eax
    push format_citire
    call [printf]
    add esp,4*2
    pop esi
    pop ecx
    loop afisare_imp
    
    push spatiu
    call [printf]
    add esp,4
    
    mov esi,P
    pop edx
    mov ecx,edx
    afisare_par:
    lodsd
    push ecx
    push esi
    push eax
    push format_citire
    call [printf]
    add esp,4*2
    pop esi
    pop ecx
    loop afisare_par
    
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului
    eroare:
    push mesaj
    call [printf]
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului