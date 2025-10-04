bits 32   
global citire

segment code use32 public code
ok dd 0

segment code use32 public code

citire:
	mov esi,[esp+4]
    mov edi,[esp+8]
    xor eax, eax            
    xor ebx, ebx             ; Acumulator pentru numar
    mov ecx, 10              

bucla:
    lodsb                    ; extragem caracterul curent în AL
    cmp al, ','              ; verificam daca este separator
    je next_number           ; salvam numarul curent in sir in caz afirmativ
    cmp al, 0                ; verificam daca este sfarsitul sirului
    je final                
    cmp al,'-'               ; verificam daca numarul urmator este negativ
    jne conversie            ; daca nu este negativ trecem direct la convertirea sa din ascii in numar 
    mov dword[ok],1          ; in ok bifam daca numarul curent este negativ sau nu
    lodsb
    
conversie:
    sub al, '0'              ; conversie ASCII -> valoare numerica
    cbw                      ; extinde AL la EAX 
    cwde                    
    xchg eax,ebx             ; in eax se afla cifra curenta si am interschimbat-o cu constructia curenta a numarului pentru a inmulti cu 10
    mul ecx                 
    xchg eax,ebx
    add ebx, eax             ; adaug cifra curenta la numar
    jmp bucla               

    
    
next_number:
    mov edx,[ok]             ;verificam daca numarul a fost negativ sau nu 
    cmp edx,1
    JNE store
    neg ebx
    store:
    mov eax, ebx             ; Mutam numarul procesat în eax
    stosd                    ; Stocam numarul curent in tabloul `sir_nr`
    xor ebx, ebx             ; Resetam acumulatorul pentru urmatorul numar
    xor edx,edx
    mov dword[ok],0
    jmp bucla               

final:
    mov edx,[ok]
    cmp edx,1
    JNE nu_e_negativ
    neg ebx
    nu_e_negativ:
    mov eax, ebx             ; Ultimul numar
    stosd                    
    mov eax, 0              
    stosd                    ; Adaugam null la final     
	ret 4*2 ; in acest caz 4 reprezinta numarul de octeti ce trebuie eliberati de pe stiva (parametrul pasat procedurii)