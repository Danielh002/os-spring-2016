#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXTHREAD 2

sem_t sem; 

void* doNothingA(void *arg){
	sleep(1);
	printf("Soy A  \n");
	sem_post(&sem);
	return 0;
}

void* doNothingB(void *arg){
	sem_wait(&sem);
	printf("Soy B \n");
	return 0;
}

int main(int argc, char** argv) {
	sem_init(&sem,0,0);
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

	