#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAXTHREAD 8
#define N 2
sem_t sem; 
int count=0;
int cantidadWaits=0;

int contador(void){
	return count++;
}

int espera(int delay){
	int r;
	srand(time(NULL));
	r= rand()%delay;
	usleep(r*1000);
	return r;
}

void* doNothing(void *arg){
	int localSum=0;
	long id = (long) arg;

	sem_wait(&sem);
	printf( "Entro el hilo con ID: %ld \n",id);
	espera(1000);
	printf( "Salio el hilo con ID: %ld \n",id);
	count++;
	sem_post(&sem);
	return 0;
}


int main(int argc, char** argv) {
	sem_init(&sem,0,N);
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		pthread_create(&threads[i], NULL, doNothing, (void*)taskids[i]);
	}
	
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&sem);
	printf("Valor count Final: %d \n",count);
	return 0;
}
