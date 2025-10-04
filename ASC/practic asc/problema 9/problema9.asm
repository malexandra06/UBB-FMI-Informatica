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

segment data use32 class=data
a dd -1
s resb 100
file_read db 'input1.txt', 0
file_out db 'output.txt', 0
format db '%s', 0
mod_in db 'r', 0
mod_out db 'w', 0
descriptor dd -1
format_ch db '%c', 0
mesaj db 'EROARE', 0
debug_msg db 'Descriptor: %d', 0

segment code use32 class=code
start:
    ; Deschidere fișier input
    push mod_in
    push file_read
    call [fopen]
    add esp, 4 * 2
    cmp eax, 0
    je eroare
    mov [descriptor], eax

    ; Debugging: afișare descriptor fișier input
    push eax
    push debug_msg
    call [printf]
    add esp, 8

    ; Procesare conținut fișier
    mov edi, s
    mov cl, 10
    bucla:
    push edi
    push ecx
        push a
        push format_ch
        push dword [descriptor]
        call [fscanf]
        add esp, 4 * 3
        cmp eax, 1
        jne ies
pop ecx
pop edi
        mov ah, 0
        mov al, [a]
        cmp al, 'a'
        jb save
        cmp al, 'z'
        ja save
        nr:
        div cl
        mov dl,ah
        mov ah,0
        div cl
        cmp al,0
        JZ jos
        add al,48
        stosb
        jos:
        xchg ah, al
        add al,48
        stosb
        mov al,dl
        add al,48
        stosb
        jmp bucla
    save:
        stosb
        jmp bucla
    ies:
    mov byte [edi], 0
    push dword [descriptor]
    call [fclose]
    add esp, 4

    ; Deschidere fișier output
    push mod_out
    push file_out
    call [fopen]
    add esp, 4 * 2
    cmp eax, 0
    je eroare
    mov [descriptor], eax

    ; Debugging: afișare descriptor fișier output
    push eax
    push debug_msg
    call [printf]
    add esp, 8

    ; Scriere conținut în fișierul output
    push s
    push format
    push dword [descriptor]
    call [fprintf]
    add esp, 4 * 3

    ; Închidere fișier și ieșire
    push dword [descriptor]
    call [fclose]
    add esp, 4
    push dword 0
    call [exit]

eroare:
    push mesaj
    call [printf]
    push dword 0
    call [exit]
