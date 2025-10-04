bits 32
global start

import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll
extern printf, exit,scanf

extern citire
;Se cere sa se citeasca de la tastatura un sir de numere, date in baza 10 ca numere cu semn (se citeste de la tastatura un sir de caractere si in memorie trebuie stocat un sir de numere).

segment data use32
format db '%s',0
format_nr db '%d',0
s resb 100
sir_nr resd 100
sep db ' ',0

segment code use32 public code
start:
    ;scanf(format,s)
	push s
    push format
    call [scanf]
    add esp,4*2
    
    ;apelam functia citire din modulul citire
    push sir_nr
    push s
    call citire
    
    ;preuspunem ca in urma functiei citire incepand cu offsetul sir_nr se afla sirul citit insa cu numere nu cu caractere
    mov esi,sir_nr
    bucla:
        lodsd ;extragem numerele din sir
        cmp eax,0 ;verificam daca nu am ajuns la sfarsitul sirului
        je iesire
        
        ;printf(format,eax)
        push eax
        push format_nr
        call [printf]
        add esp,4*2
        
        ;afisam si un spatiu intre numere
        push sep
        call [printf]
        add esp,4*2
        JMP bucla ;parcurgem bucla pana cand se ajunge la caracterul null
    iesire:
	push 0
	call [exit]