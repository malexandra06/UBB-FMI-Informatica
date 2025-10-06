/*Programul apelat primeste ca argumente un nume de fisier si une sir de caractere si scrie in fisier sirul oglindit. Programul apelat citeste niste siruri de caractere si concateneaza oglindirile lor.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAXIM 100

int main(int argc, char* argv[])
{
    char string[MAXIM * argc + 1];
    string[0] = '\0'; // Initializare!

    for (int i = 1; i < argc; i++)
    {
        if (fork() == 0)
        {
            execlp("./apelat2", "./apelat2", argv[i], "output.txt", NULL);
            perror("Eroare execlp"); // important în caz că eșuează
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }

    char sir[MAXIM];
    FILE* fd = fopen("output.txt", "r");
    if (fd == NULL) {
        perror("Eroare deschidere fisier output.txt");
        return 1;
    }

    while (fscanf(fd, "%s", sir) == 1)
    {
        strcat(string, sir);
    }
    fclose(fd);

    printf("%s\n", string);
    return 0;
}

