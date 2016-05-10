#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXTHREAD 5

sem_t palillo[MAXTHREAD];

/*gcc -std=c99 -pthread filosofos.c -o p.exe  */

void* doNothing(void *arg){
    long id = (long) arg;
    printf("Filosofo: %ld esta pensando \n",id);  
	sem_wait(&palillo[id]);
	sem_wait(&palillo[(id+1)%5]);
	printf("Filosofo: %ld esta Comiendo \n",id);  
	sem_post(&palillo[id]);
	sem_post(&palillo[(id+1)%5]);
	return 0;
}


int main(int argc, char** argv) {
	sem_init(&palillo[0],0,1);
	sem_init(&palillo[1],0,1);
	sem_init(&palillo[2],0,1);
	sem_init(&palillo[3],0,1);
	sem_init(&palillo[4],0,1);
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
        pthread_create(&threads[i], NULL, doNothing, (void*)taskids[i]);
	}
	
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&palillo[0]);
	sem_destroy(&palillo[1]);
	sem_destroy(&palillo[2]);
	sem_destroy(&palillo[3]);
	sem_destroy(&palillo[4]);
	
	return 0;
}