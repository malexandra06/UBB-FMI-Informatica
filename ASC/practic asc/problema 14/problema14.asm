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

;Se da fișierul ala "preufung.txt", câte conține un text de maxim 200 caractere, conține litere mici, mari, spatii și puncte. 
;Afiseaza pe ecran pe randuri diferite cuvintele cu nr impar de litere și sa se înlocuiască litera din mijloc cu spatiu

segment data use32 class=data
cuv resb 100
len db 0

filename db 'input.txt',0
mod_acces db 'r',0
descriptor dd -1
format_ch db '%c',0
format_sir db '%s',0
car dd 0
newline db 10,0
mesaj db 'Eroare...',0
segment code use32 class=code
start:
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    cmp eax,0
    je eroare
    mov [descriptor],eax
    mov edi,cuv
    bucla:
        ;fscanf(descriptor,format,c)
        push car
        push format_ch
        push dword[descriptor]
        call [fscanf]
        add esp,4*3
        
        mov al,[car]
        stosb
        cmp al,0
        JE iesi
        cmp al,' '
        JE next_cuv
        inc byte[len]
        JMP bucla
        next_cuv:
            test byte[len],1
            JZ cuv_par
            mov eax,0
            mov al,[len]
            mov ah,0
            mov dl,2
            div dl
            mov ah,0
            mov byte[eax+cuv],' '
            mov eax,0
            mov al,[len]
            mov byte[cuv+eax],0
            push cuv
            push format_sir
            call [printf]
            add esp,4*2
            
            push newline
            push format_sir
            call [printf]
            add esp,4*2
            cuv_par:
                mov edi,cuv
                mov byte[len],0
                JMP bucla
    iesi:
    test byte[len],1
            JZ jos
            mov eax,0
            mov al,[len]
            mov ah,0
            mov dl,2
            div dl
            mov ah,0
            mov byte[eax+cuv],' '
            mov eax,0
            mov al,[len]
            mov byte[cuv+eax],0
            push cuv
            push format_sir
            call [printf]
            add esp,4*2
            
         jos:
    ;fclose(descriptor)
    push dword[descriptor]
    call[fclose]
    add esp,4
    
    
    push dword 0
    call [exit]
    eroare:
    push mesaj
    call [printf]
    add esp,4
    push dword 0
    call [exit]

   