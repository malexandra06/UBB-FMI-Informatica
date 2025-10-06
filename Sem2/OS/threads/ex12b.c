#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int** mat;
int m, n;
int total=0;
pthread_mutex_t mtx;

void* routine(void* arg) {
    	int suma=0;
	int line=*(int*)arg;
	
	for(int i=0;i<n;i++)
		suma+=mat[line][i];
	*(int*)(arg)=suma;
	return arg;
}

int main(int argc, char* argv[]) {
    FILE* fd = fopen(argv[1], "r");
    fscanf(fd, "%d", &m);
    fscanf(fd, "%d", &n);
	printf("%d %d\n",m,n);
    pthread_mutex_init(&mtx,NULL);
    mat = malloc(m * sizeof(int*));
    pthread_t th[m];
    for (int i = 0; i < m; i++) {
        mat[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            fscanf(fd, "%d", &mat[i][j]);
    }
    fclose(fd);
    int i;
    for(i=0;i<m;i++)
    {
	int* arg=malloc(sizeof(int));
	*arg=i;
	pthread_create(&th[i],NULL,routine,(void*)arg);
    }
    
     for(i=0;i<m;i++)
    {
	int* rez;
        pthread_join(th[i],(void**)&rez);
	printf("Suma facuta de thread-ul %d este %d\n",i,*rez);
	total+=*rez;
	free(rez);
    }
    pthread_mutex_destroy(&mtx);
    for (i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
    printf("Suma este %d\n",total);
    return 0;
}
