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


;20.	Se citeste de la tastatura un cuvant si un numar. Daca numarul este par se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului 20. Daca numarul este impar se cere criptarea cuvantului prin adaugarea dupa fiecare vocala a gruparii "p"+vocala.Se cere afisarea cuvantului criptat.

;ex: arici 3 => aparipicipi



segment data use32 class=data

n dd 0
cuv resb 100
criptat resb 200
format_sir db '%s',0
format_nr db '%u',0
vocale db 'aeiou'

segment code use32 class=code
start:
    
    ;scanf(%s,cuv)
    push cuv 
    push format_sir
    call [scanf]
    add esp,4*2
    
    ;scanf(%u,&n)
    push n 
    push format_nr
    call [scanf]
    add esp,4*2
    
    test dword[n],1
    JZ par_et
    push vocale
    push criptat
    push cuv
    call impar
    JMP afisare
    par_et:
        push criptat
        push cuv
        call par
    afisare:
        push criptat
        push format_sir
        call [printf]
    push dword 0
    call [exit]

impar:
    mov edi, [esp+8]
    mov esi, [esp+4]
    mov ebx, [esp+12]
    criptare:
           lodsb
           cmp al,0
           JE final2
           mov dl,al
           stosb
           mov ecx,5
           mov ebx,[esp+12]
           verific:
           cmp byte[ebx],dl
           JE ies
           inc ebx
           loop verific
           JMP criptare
           ies:
              mov al,'p'
              stosb
              mov al,dl
              stosb
              JMP criptare
    final2:
        mov byte [edi],0
        ret 4*3
    

par:
     mov esi,[esp+4]
     mov edi,[esp+8]
     transformare:
           lodsb
           cmp al,0
           JE final1
           add al,20
           stosb
           JMP transformare
    final1:
        mov byte[edi],0
        ret 4*2
   