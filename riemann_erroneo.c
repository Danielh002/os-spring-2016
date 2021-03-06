/**
* FILE: riemann_erroneo.c
* DESCRIPTION:
* 	Implementacion de la suma de Riemann para calcular el area bajo la
*	curva. Este codigo esta errado, usted debe hacer los ajustes para que
*	funcionen correctamente.
* AUTHOR: John Sanabria - john.sanabria@correounivalle.edu.co
* LAST REVISED: 14/04/16
* REFERENCES: http://mathinsight.org/calculating_area_under_curve_riemann_sums
******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0
//Tipo de dato sem_t y gestions de hilos
#include <semaphore.h> 

sem_t sem;
double length = LIMIT - BASE;
double numRectxThread = (double)(MAXRECT/MAXTHREAD);
double base_length = 0;
double sumTotal = 0;

double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	long id = (long) arg;
	double lowlimit = id*base_length*numRectxThread;
	double localSum=0;

	for (int i = 0; i < numRectxThread; i++) {
		
		localSum += function(lowlimit + i*base_length) * base_length;
		
	}
	sem_wait(&sem);
	sumTotal+=localSum;
	sem_post(&sem);
	return 0;
}

int main(int argc, char** argv) {
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];

	base_length = length/MAXRECT;
	sem_init(&sem,0,1);
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		pthread_create(&threads[i], NULL, calcular, (void*)taskids[i]);
	}
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&sem);
	printf("Suma total %lf\n",sumTotal);
	pthread_exit(NULL);
}
