bits 32
global start
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll
extern printf, exit,scanf,fopen,fscanf,fclose

segment data use32
a dd 0                      ; Variabilă pentru numărul citit
minn db 16                  ; Variabilă pentru minimul curent
sir_min resb 100            ; Șirul cifrelor minime
len db 0                    ; Lungimea șirului de minime
nume_fisier db 'input.txt', 0
mod_acces db 'r', 0
mesaj_eroare db 'Nu s-a putut citi din fisierul', 0
descriptor dd -1            ; Descriptorul fișierului
format_citire db '%x', 0    ; Format de citire pentru numere hexazecimale
format_afis db '%u ', 0     ; Format pentru afișarea cifrelor minime

segment code use32 public code
start:
    ; Deschiderea fișierului
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 4*2
    cmp eax, 0
    je eroare_la_deschidere
    mov [descriptor], eax
    mov edi, sir_min

    ; Bucla principală
bucla:
    push dword a
    push dword format_citire
    push dword [descriptor]
    call [fscanf]
    add esp, 4*3

    ; Verificare rezultat fscanf
    cmp eax, 1             ; Dacă nu s-a citit un număr
    jl iesire              ; Ieșire din buclă

    ; Resetare pentru un nou număr
    mov byte [minn], 16    ; Resetare minim

    ; Procesare cifre hexazecimale
    mov ebx, [a]           ; Numărul citit
procesare_cifre:
    test ebx, ebx          ; Verifică dacă mai sunt cifre
    jz final_cifre         ; Dacă nu mai sunt, termină
    mov edx, ebx           ; Obține ultima cifră
    and edx, 0xF           ; Extrage cifra hexazecimală
    cmp dl, byte [minn]
    ja skip_minim
    mov byte [minn], dl    ; Actualizează minimul
skip_minim:
    shr ebx, 4             ; Treci la următoarea cifră
    jmp procesare_cifre

final_cifre:
    ; Salvează minimul în șir
    inc byte [len]
    mov al, [minn]
    stosb
    jmp bucla

iesire:
    ; Închide fișierul
    push dword [descriptor]
    call [fclose]
    add esp, 4

    ; Afișare cifre minime
    mov ecx, 0
    mov cl, [len]
    cld
    mov esi, sir_min
afisare:
    mov eax,0
    push ecx
    lodsb
    push eax
    push dword format_afis
    call [printf]
    add esp, 4*2
    pop ecx
    loop afisare

    ; Terminare program
    push 0
    call [exit]

eroare_la_deschidere:
    push dword mesaj_eroare
    call [printf]
    add esp, 4
    push 0
    call [exit]
