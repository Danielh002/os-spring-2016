#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAXTHREAD 2
#define MAXITEMS 10

sem_t semaforo;
int espaciosRestantes=MAXITEMS;
int itemsProducidos;

void * producir(){
	if (espaciosRestantes==0){
		printf("No hay espacio para producir");
		sem_wait(&semaforo);
	}
	else{
		sem_post(&semaforo);
		itemsProducidos++;
		espaciosRestantes--;
	}
}

void * consumir(){
	if (itemsProducidos==0){
		printf("No hay que nada que consumir");
		sem_wait(&semaforo);
	}
	else{
		sem_post(&semaforo);
		itemsProducidos--;
		espaciosRestantes++;
	}
}

int main(int argc, char** argv) {
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];
	sem_init(&semaforo,0,0);
	
	pthread_create(&threads[1], NULL, producir, (void*)taskids[1]);
	pthread_create(&threads[0], NULL, consumir, (void*)taskids[0]);
	
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&semaforo);
	return 0;
}



