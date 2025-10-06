/* RO: Copiati acest fisier intr-un alt fisier cu extensia .c (de
* exemplu a.c) si rezolvati problemele compilare (erori si warning-uri)
* si rulare (folositi valgrind), incat programul sa citeasca trei
* propozitii din linia de comanda si sa creeze apoi un fisier out.txt
* in care va scrie propozitiile citite inlocuind literele mari cu litere
* mici si literele mici cu litere mari.
*
* EN: Copy this file to another file having a .c extension (eg a.c) and
* fix the compilation errors/warnings and the runtime problems (use
* valgrind), so that the program will read three sentences from the
* command line, and then will create a file out.txt in which it will
* write the sentences replacing lower case letters with upper case
* letters and upper case letters with lower case letters.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    char* s[3];
    int i, j, offset;
    FILE* fd;
    for(i=0; i<3; i++) {
        s[i] = (char*)malloc(128*sizeof(char));
        if(fgets(s[i], 128, stdin) == NULL) {
            perror("Error reading the sentence");
            return 1;
        }
    }

    offset = 'a' - 'A';
    for(i=0; i<3; i++) {
        for(j=0; j<(int)strlen(s[i]); j++) {
            if(s[i][j] >= 'a' && s[i][j] <= 'z') {
                s[i][j] -= offset;
            }
            else if(s[i][j] >= 'A' && s[i][j] <= 'Z') {
                s[i][j] += offset;
            }
        }
    }
	
    fd = fopen("out.txt", "w");
    if(fd ==NULL) {
        perror("Failed to create the output file");
        return 1;
    }
    for(i=0; i<3; i++) {
        fwrite(s[i],strlen(s[i]),sizeof(char),fd);
        free(s[i]);
    }
    fclose(fd);

    return 0;
}
 
