bits 32

extern _citireSirC
global _citire_nr
;nasm modul.asm -fwin32 -g -o modul.obj

segment data public data use32
    adresaSirRezultat     dd        0
    adresaSirParam        dd        0
    adresaSirCitit        dd        0
    ok dd 0
    

segment code use32 public code
_citire_nr:
    ; Parametri:
    ; sir: [esp + 4] - adresa sirului de caractere
    ; numere: [esp + 8] - adresa sirului pentru numere

    push ebp
    mov ebp, esp
    sub esp, 4 * 3                    ; rezervam pe stiva 4*3 de octeti pentru sirul citit de la tastatura
   
    ; la locatia [ebp+4] se afla adresa de return (valoarea din EIP la momentul apelului)
    ; la locatia [ebp] se afla valoarea ebp pentru apelant
    
    mov eax, [ebp + 8]
    mov [adresaSirParam], eax  ;in adresaSirParam avem adresa sirului de caractere citit
    mov eax, [ebp + 12]
    mov [adresaSirRezultat], eax ;in adresaSirRezultat avem adresa sirului de numere
    
    ; salvam adresa sirului care va fi citit
    mov [adresaSirCitit], ebp
    sub dword [adresaSirCitit], 4*3
    push dword [adresaSirCitit]
    
    mov edi, [adresaSirRezultat]
    mov esi, [adresaSirParam]
    xor eax, eax             
    xor ebx, ebx             
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
    
    add esp,4*2
    mov esp, ebp
    pop ebp
	ret
