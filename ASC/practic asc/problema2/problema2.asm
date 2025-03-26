bits 32 ;asamblare si compilare pentru arhitectura de 32 biti
; definim punctul de intrare in programul principal
global  start 
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll
extern printf, exit,scanf,fopen,fscanf,fclose,fprintf
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante
        
        
;2.	Se citește de la tastatură un număr N și apoi N numere.
;Să se calculeze suma numerelor pare introduse, să se calculeze suma numerelor impare introduse, apoi diferența dintre cele două sume.
;Să se afișeze în fișierul output.txt cele 3 rezultate, în baza 16, pe linii separate.

segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
n dd -0
a dd 0
filename db 'output.txt',0
mod_acces db 'w',0
descriptor dd -1
format db '%u',0
format_afis db '%u ',0
segment  code use32 class=code ; segmentul de cod
start: 
    ;scanf(format,n)
    push dword n
    push dword format
    call [scanf]
    add esp,4*2
    
    mov ecx,[n]
    mov ebx,0 ;suma numerelor pare
    mov edx,0 ;suma numerelor impare
    bucla_citire:
    pushad
    ;scanf(format,a)
    push dword a
    push dword format
    call [scanf]
    add esp,4*2
    popad
    mov eax,[a]
    test eax,1
    JNZ impar
    par:
        add ebx,eax
        JMP final
    impar:
        add edx,eax
    final:
    loop bucla_citire
    pushad
    ;fopen(nume_fisier,mod_acces)
    push mod_acces
    push dword filename
    call [fopen]
    add esp,4*2
    cmp eax,0
    JZ eroare
    mov [descriptor],eax
    
    popad
    mov eax,ebx
    sub eax,edx
    ;fprintf(descriptor,format_afis,variabile)
    push eax
    push edx
    push ebx
    push format_afis
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    push format_afis
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    push format_afis
    push dword[descriptor]
    call [fprintf]
    add esp,4*3
    push dword[descriptor]
    call [fclose]
    add esp,4
	push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului
    eroare:
    push   dword 0 ;se pune pe stiva codul de retur al functiei exit
	call   [exit] ;apelul functiei sistem exit pentru terminarea executiei programului