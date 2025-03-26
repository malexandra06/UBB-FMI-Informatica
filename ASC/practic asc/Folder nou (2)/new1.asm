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




segment data use32 class=data
filename resb 50
sir resb 100
format_sir db '%s',0
tabHexa db '0123456789ABCDEF',0
mod_acces db 'r',0
descriptor dd -1
len equ 100
len_sir dd 0
vocale db 'aeiouAEIOU',0
format_af db '%u',0
nr resb 100
lg db 0
format_ch db '%c',0
segment code use32 class=code
start:
    push filename
    push format_sir
    call [scanf]
    add esp,4*2
    
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    mov [descriptor],eax
    
    ;fread(sir,1,len,descriptor)
    push dword[descriptor]
    push len
    push 1
    push sir
    call [fread]
    add esp,4*4
    
    mov [len_sir],eax
    
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    
    ;push vocale
    ;push dword[len_sir]
    ;push sir
    ;call numara
    ;add esp,4*3
    
    numara:
        mov esi,sir
        mov ecx,[len_sir]
        mov edx,0
        parcurgere:
            lodsb
            
            push ecx
            push esi
            verific_litera:
                cmp al,'A'
                JB iesire
                cmp al,'z'
                JA iesire
                cmp al,'Z'
                JBE litera
                cmp al,'a'
                JB iesire
            litera:
            mov ecx,10
            mov esi,vocale
            mov bl,al
            verific_consoana:
                lodsb
                cmp bl,al
                JE iesire
            loop verific_consoana
            INC EDX
            iesire:
                pop esi
                pop ecx
        loop parcurgere
    
   
    
    mov ecx,16
    mov ebx,tabHexa
    mov edi,nr
    mov eax,edx
    impart:
        
        mov edx,0
        div ecx
        xchg al,dl
        stosb
        xchg al,dl
        inc byte[lg]
        cmp eax,0
        JNE impart
    
    mov eax,nr
    mov ebx,tabHexa
    xlat
    mov edi,nr
    mov ecx,0
    mov cl,[lg]
    std
    add edi,ecx
    dec edi
    afis:
        lodsb
        push ecx
        push edi
        mov bl,al
        mov eax,0
        mov al,bl
        push eax
        push format_ch
        call [printf]
        pop edi
        pop ecx
    loop afis
    push dword 0
    call [exit]

    
    