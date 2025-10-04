#include <stdio.h>

// functia declarata in fisierul modul.asm
void citire_nr(char sir[], int sirR[]);

// functia folosita pentru a citi un sir de la tastatura
void citireSirC(char sir[]);


int main()
{
    char str[100];
    int Rez[100];
    printf("Sirul 1 citit din modulul C: ");
    citireSirC(str);
    citire_nr(str,Rez);
    printf("Numerele convertite sunt: ");
    for (int i = 0; i < 100; i++) {
        if (Rez[i] == 0) break;  // Oprim afișarea la numerele care sunt 0 (numărul de elemente valide)
        printf("%d ", Rez[i]);
    }
    printf("\n");
    return 0;
}

void citireSirC(char sir[])
{
    scanf("%s", sir);
}