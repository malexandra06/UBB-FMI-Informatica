/*Scrieti un program C care creeaza doua procese fiu. Cele doua procese isi vor trimite alternativ numere intregi intre 1 si 10 (inclusiv) pana cand unul din ele trimite numarul 10. Afisati mesaje pe masura ce numerele sunt trimise.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    
    srandom(time(NULL)); // Inițializare generator numere aleatoare
    
    int pid1 = fork();
    if (pid1 == 0) { // Primul copil
        close(fd1[0]); // Închidem capătul de citire al primului pipe
        close(fd2[1]); // Închidem capătul de scriere al celui de-al doilea pipe
        
        int n = 1; // Valoare de start
        while (1) {
            // Scriem numărul generat
            n = random() % 10 + 1;
            printf("[CHILD1] Trimit %d\n", n);
            write(fd1[1], &n, sizeof(int));
            
            if (n == 10) {
                printf("[CHILD1] Am trimis 10. Ies.\n");
                break;
            }
            
            // Așteptăm răspunsul
            read(fd2[0], &n, sizeof(int));
            printf("[CHILD1] Am primit %d\n", n);
            
            if (n == 10) {
                printf("[CHILD1] Am primit 10. Ies.\n");
                break;
            }
        }
        
        close(fd1[1]);
        close(fd2[0]);
        exit(0);
    }
    
    int pid2 = fork();
    if (pid2 == 0) { // Al doilea copil
        close(fd2[0]); // Închidem capătul de citire al celui de-al doilea pipe
        close(fd1[1]); // Închidem capătul de scriere al primului pipe
        
        int n;
        while (1) {
            // Așteptăm numărul
            read(fd1[0], &n, sizeof(int));
            printf("[CHILD2] Am primit %d\n", n);
            
            if (n == 10) {
                printf("[CHILD2] Am primit 10. Ies.\n");
                break;
            }
            
            // Răspundem cu un număr nou
            n = random() % 10 + 1;
            printf("[CHILD2] Trimit %d\n", n);
            write(fd2[1], &n, sizeof(int));
            
            if (n == 10) {
                printf("[CHILD2] Am trimis 10. Ies.\n");
                break;
            }
        }
        
        close(fd2[1]);
        close(fd1[0]);
        exit(0);
    }
    
    // Părintele
    close(fd1[0]); close(fd1[1]);
    close(fd2[0]); close(fd2[1]);
    
    wait(NULL);
    wait(NULL);
    return 0;
}
