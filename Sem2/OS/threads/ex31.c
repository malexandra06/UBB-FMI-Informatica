/*Stafeta: Creati un program C care citeste un numar n de la tastatura si creeaza 4 * n thread-uri. Thread-urile vor fi impartite in "echipe" de cate 4. In fiecare "echipa" thread-urile vor fi numerotate incepand cu 0 si vor rula dupa regula stafetei:
- Thread-ul 0 din fiecare "echipa" incepe, asteapta (usleep) un timp intre 100 si 200 de milisecunde, apoi transfera controlul thread-ului 1
- Thread-ul 1 asteapta intre 100 si 200 de milisecunde apoi transfera controlul thread-ului 2
- Thread-ul 2, similar, asteapta intre 100 si 200 de milisecunde apoi transfera controlul thread-ului 3
- Thread-ul 3 asteapta intre 100 si 200 de milisecunde, dupa care afiseaza un mesaj si isi incheie executia
"Echipa" din care thread-ul 3 isi incheie executia primul este castigatoare. Folositi mecanisme de sincronizare corespunzatoare.*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n;

int main()
{
	printf("Introduceti n=");
	scanf("%d",&n);

	pthread_t th1[n];
	pthread_t th2[n];
	pthread_t th3[n];
	pthread_t th4[n];

	for(int i=0;i<4*n;i++)
	{
		if(i<n)
			pthread_create(&th1[i],NULL,routine,NULL);
		else if(i>=n && i<2*n)
			pthread_create(&th2[i%n],NULL,routine,NULL);
		else if(i>=2*n && i<3*n)
                        pthread_create(&th3[i%n],NULL,routine,NULL);
		else if(i>=3*n && i<4*n)
                        pthread_create(&th4[i%n],NULL,routine,NULL);
	}

	for(int i=0;i<4*n;i++)
        {
                if(i<n)
                        pthread_join(th1[i],NULL);
                else if(i>=n && i<2*n)
                        pthread_join(th2[i%n],NULL);
                else if(i>=2*n && i<3*n)
                        pthread_join(th3[i%n],NULL);
                else if(i>=3*n && i<4*n)
                        pthread_join(&th4[i%n],NULL);
        }
	return 0;
}
