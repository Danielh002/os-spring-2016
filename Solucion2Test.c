#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXTHREAD 2

sem_t sem; 
sem_t sem2; 

void* doNothingA(void *arg){;
	printf("Soy A1  \n");
	sem_post(&sem);
	sem_wait(&sem2);
	printf("Soy A2 \n");
	return 0;
}

void* doNothingB(void *arg){
	printf("Soy B1 \n");
	sem_post(&sem2);
	sem_wait(&sem);
	printf("Soy B2 \n");
	return 0;
}

int main(int argc, char** argv) {
	sem_init(&sem,0,0);
	sem_init(&sem2,0,0);
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];
	pthread_create(&threads[1], NULL, doNothingB, (void*)taskids[1]);
	pthread_create(&threads[0], NULL, doNothingA, (void*)taskids[0]);
	
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&sem);
	return 0;
}
