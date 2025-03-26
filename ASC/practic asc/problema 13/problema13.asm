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

;13.	Se citeste de la tastatura un cuvant (sir de caractere de maxim 20 de caractere) si un numar reprezentat pe un octet.
;Daca numarul este impar se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului citit modulo 20. Daca numarul este par se cere criptarea cuvantului prin adaugarea dupa fiecare consoana a gruparii "p"+consoana. Se cere afisarea cuvantului criptat

segment data use32 class=data
criptat resb 200
a resb 100
format_sir db '%s',0
n dd 0
format_nr db '%u',0
vocale db 'aeiou',0
segment code use32 class=code
start:
    push a 
    push format_sir
    call [scanf]
    add esp,4*2
    
    push n
    push format_nr
    call [scanf]
    add esp,4*2
    
    mov esi,a 
    mov edi,criptat
    test byte[n],1
    JZ par
    mov ah,0
    mov al,[n]
    mov dl,20
    div dl
    bucla:
        lodsb
        cmp al,0
        je iesi
        add al,ah
        stosb
        JMP bucla
    par:
        lodsb
        cmp al,0
        je iesi
        stosb
        mov ecx,5
        mov ebx,vocale
        compar:
            cmp al,byte[ebx]
            JE nu_e_consoana
            inc ebx
        loop compar
        add al,'p'
        stosb
        jmp par
        nu_e_consoana:
            jmp par
    iesi:
    push criptat
    push format_sir
    call [printf]
    push dword 0
    call [exit]

   