bits 32 
global start

extern exit, fopen, fclose,printf,fread ; adaugam fopen si fclose ca functii externe           
import exit msvcrt.dll     
import fopen msvcrt.dll     ; indicam asamblorului ca functia fopen se gaseste in libraria msvcrt.dll
import fclose msvcrt.dll      ; similar pentru fclose
import printf msvcrt.dll
import fread msvcrt.dll

;Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de consoane si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date.

segment data use32 class=data
    fisier_citire db 'data.txt',0
    mod_acces_1 db "r",0
    descriptor dd -1
    len equ 100   ;presupunem ca citim un text de maxim 100 de caractere
    s times len db 0 ;in s vom retine sirul citit
    sir_vocale db 'a','e','i','o','u','A','E','I','O','U'
    format_afisare db '%u',0
    lens resd 1 ;retinem numarul de caractere citite din fisier
    eroare db 'Nu s-a citit fisierul',0
    
    
segment code use32 class=code
start:
    ;fopen(nume_fisier,mod_acces)
    ;deschidem fisierul de citire
    push dword mod_acces_1
    push dword fisier_citire
    call [fopen]
    ADD ESP,4*2
    CMP EAX,0 ;EAX va retine descriptorul de fisier iar in cazul in care nu s-a citit se va afisa un mesaj de eroare
    JE final
    
    Mov [descriptor],EAX ;retinem in variabila descriptor descriptorul de fisier
    
    ; citim textul in fisierul deschis folosind functia fread
    ; eax = fread(text, 1, len, descriptor_fis)
    push dword [descriptor]
    push dword len ;presupunem ca citim un text de maxim 100 de caractere
    push dword 1   ;se citeste caracter cu caracter
    push dword s   ;se retine in s   
    call [fread]
    mov [lens],eax ;dupa apelul functiei fread EAX contine numarul de caractere citite din fisier,iar s sirul citit din fisier
    add esp, 4*4 
        
    ; apelam functia fclose pentru a inchide fisierul
    ; fclose(descriptor_fis)
    push dword [descriptor]
    call [fclose]
    add esp, 4
        
   
    mov edx,0 ;in edx retinem numarul de consoane
    mov ESI,s ;cu ajutorul lui esi parcurgem s
    mov ecx,[lens]; retinem in ecx numarul de caractere citite pentru a efectua loop-ul
    bucla:
        MOV AL,[ESI] ;extragem cate un caracter din s
        push ecx
        mov ecx,10   ;mutam in ecx lungimea sirului de vocale pentru a compara ulterior caracterul curent din sir cu fiecare vocala
        mov EDI,sir_vocale ;cu edi parcurgem sirul de vocale
        verifica_vocale:
            mov BL,[EDI] ;extragem cate o vocala
            INC EDI
            CMP AL,BL    ;comparam cu caracterul curent din s
            JZ final_bucla ;daca s-a gasit o vocala se iese din bucla
        loop verifica_vocale
        verifica_litera:
            CMP AL,'A'    ;daca caracterul curent are codul ascii mai mic decat A clar nu e litera deci trecem la urmatorul caracter
            JB final_bucla
            CMP AL,'z'    ;la fel si in cazul in care codul ascii este mai mare decat a lui z
            JA final_bucla
            CMP AL,'a'    ;momentan stim ca 'A'<=AL<='z',iar daca AL>='a' rezulta ca este litera
            JAE count
            CMP AL,'Z'    ;stim ca 'A'<=AL<='a'<='z', iar daca AL>'Z' atunci nu este litera 
            JA final_bucla
    count:
        inc edx
    final_bucla:
    pop ecx ;restauram valoarea lui ecx
    INC ESI
    loop bucla
    
    ;printf(format_afisare,edx) afisam numarul de consoane din sir pe ecran
    push edx
    push format_afisare
    call [printf]
    
    push dword 0
    call [exit]
    ;in cazul in care fisierul nu a putut fi deschis
    final:
    push dword eroare
    call [printf]
