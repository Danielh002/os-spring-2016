#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXTHREAD 2

sem_t sem; 
int count=0;

int contador(void){
	return count++;
}


void* doNothing(void *arg){
	int localSum=0;
	sem_wait(&sem);
	localSum += contador();
	printf("Valor count: %d \n",count);
	sem_post(&sem);
	return 0;
}


int main(int argc, char** argv) {
	sem_init(&sem,0,1);
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];
	pthread_create(&threads[1], NULL, doNothing, (void*)taskids[1]);
	pthread_create(&threads[0], NULL, doNothing, (void*)taskids[0]);
	
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&sem);
	printf("Valor count Final: %d \n",count);
	return 0;
}

	