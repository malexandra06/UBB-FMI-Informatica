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


;19.	Sa se citeasca de la tastatura un numar n, apoi sa se citeasca mai multe cuvinte, pana cand se citeste cuvantul/caracterul "#". Sa se scrie intr-un fisier text toate cuvintele citite care incep si se termina cu aceeasi litera si au cel putin n litere.


segment data use32 class=data

n dd 0
cuv resb 100
filename db 'output.txt',0
mod_acces db 'a',0
descriptor dd -1
format_sir db '%s',0
format_nr db '%u',0
format_fis db '%s ',0

segment code use32 class=code
start:
    ;scanf(%u,&n)
    push n 
    push format_nr
    call [scanf]
    add esp,4*2
    
    ;fopen(filename,mod_acces)
    push mod_acces
    push filename
    call [fopen]
    add esp,4*2
    
    mov dword[descriptor],eax
    
    citire:
          push cuv
          push format_sir
          call [scanf]
          add esp,4*2
          cmp byte[cuv],'#'
          JE iesire
          mov esi,cuv
          mov edx,0
          mov bl,byte[cuv]
          parcurgere:
                    lodsb
                    cmp al,0
                    JE final_sir
                    inc edx
                    JMP parcurgere
          final_sir:
                   mov al,byte[esi-2]
                   cmp al,bl 
                   JNE citire
                   cmp edx,dword[n]
                   JB citire
                   ;fprintf(descriptor,format,sir)
                   push cuv 
                   push format_fis
                   push dword[descriptor]
                   call [fprintf]
                   add esp,4*3
                   JMP citire
    iesire:
    
    ;fclose(descriptor)
    push dword[descriptor]
    call [fclose]
    add esp,4
    
    push dword 0
    call [exit]

   